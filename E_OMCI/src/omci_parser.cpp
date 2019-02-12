#include <common.hpp>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <fstream>
#include <istream>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <omci_parser.hpp>


using namespace std;


OMCI_Parser::OMCI_Parser()
{
    get_cfg();
    get_omci_playback_data();
}


void OMCI_Parser::omci_play_back()
{
    UI16_T i     = 0;
    UI16_T delay = 0;

    UI16_T key = 0;

    std::vector<long long> dA;

    // ------------------------------------------------------------------
    // 1. Cal delay time between two omci .
    // ------------------------------------------------------------------
    //

    for (auto &J : m_omci_playback) 
    {
        Json::Value playback = J.second; 
        long long t = playback["Create_Time"].asUInt64();
        dA.push_back(t);
        i++;
    }

    i=0;

    for (auto &K : m_omci_playback) 
    {
        Json::Value playback = K.second; 
        long long delay = dA[i+1] - dA[i];
        printf("delay [%ll]\r\n", delay);

        printf("raw[%d][%s]\r\n",i,  playback["Raw_Data"].asString().c_str());

        if(delay > 0)
            usleep(delay); 
        i++;
    }
}


void OMCI_Parser::get_omci_playback_data()
{
    if(is_omci_play_enable())
    {
        std::string ME_PLAYBACK_DIR(m_playback_cfg["OMCI_PLATBACK_FILE_PATH"].asString());
        struct dirent *entry;

        DIR *dir = opendir(ME_PLAYBACK_DIR.c_str());

        if (dir == NULL) 
        {
            printf("[%s]no such path [%s] exist!!\r\n", __MY_FILE__, ME_PLAYBACK_DIR.c_str());
            return;
        }

        while ((entry = readdir(dir)) != NULL) 
        {
            std::string dot(".");
            std::string ddot("..");

            std::string tmp_me_name = entry->d_name;

            if((dot == tmp_me_name) || (ddot == tmp_me_name))
                continue;

            std::string trans_cid = tmp_me_name.substr(0, tmp_me_name.find("_"));
            printf("[%s]me name[%s] me cid[%s]\r\n", __MY_FILE__, tmp_me_name.c_str(), trans_cid.c_str());

            std::string m_config_file_path = ME_PLAYBACK_DIR + tmp_me_name ;
            printf("[%s]new pathname[%s]\r\n",__MY_FILE__,  m_config_file_path.c_str());

            ifstream    source_files= {};

            source_files.open(m_config_file_path);

            if(source_files.good())
            {   
                Json::Value omci_s;
                Json::Reader reader;
                BOOL_T isJsonOK = (reader.parse(source_files, omci_s));

                if(isJsonOK)
                {
                    printf("[%s]Get playback omci_s ok \r\n", __MY_FILE__);
                    printf("[%s]Class id:%d\r\n", __MY_FILE__, omci_s["Class"].asInt());
                    int Class =  omci_s["Class"].asInt();
                    m_omci_playback[std::stoi(trans_cid)]=omci_s; 
                    m_playback_omci_num++;
                    printf("[%s]m_playback_omci_num size is %zu\r\n",__MY_FILE__ ,m_omci_playback.size());
                }
                else
                {
                    printf("[%s]Get omci_s ng\r\n", __MY_FILE__);
                    return;
                }
            }
            else
            {
                printf("[%s]Open file NG\r\n", __MY_FILE__);
                return;
            }
        }
        closedir(dir);
    }
    return;
}

void OMCI_Parser::get_cfg()
{
    // ------------------------------------------------------------------
    // Prepare PlayBack_Cfg data . 
    // ------------------------------------------------------------------
    ifstream    m_source_files= {};
    std::string t_path = PLAYBACK_CFG_NAME;

    m_source_files.open(t_path);

    if(m_source_files.good())
    {   
        Json::Reader reader;
        BOOL_T isJsonOK = (reader.parse(m_source_files, m_playback_cfg));

        if(isJsonOK)
        {
            printf("[%s]Get PlayBack_Cfg OK \r\n", __MY_FILE__);
            printf("[%s]PLAYBACK Enable[%d]\r\n", __MY_FILE__, m_playback_cfg["PLAYBACK"].asInt());
            printf("[%s]RECORD PLAYBACK Enable[%d]\r\n", __MY_FILE__, m_playback_cfg["RECORD_PLAYBACK"].asInt());
            printf("[%s]OMCI_PLATBACK_FILE_PATH[%s]\r\n", __MY_FILE__, m_playback_cfg["OMCI_PLATBACK_FILE_PATH"].asString().c_str());
            printf("[%s]OLT_PLATBACK_FILE_PATH[%s]\r\n", __MY_FILE__, m_playback_cfg["OLT_PLATBACK_FILE_PATH"].asString().c_str());
        }
        else
        {
            printf("[%s]Get PlayBack_Cfg NG, Check JSON format !!!\r\n", __MY_FILE__);
        }
    }
    else
    {
        printf("[%s]Open PlayBack_Cfg NG\r\n", __MY_FILE__);
    }

    // ------------------------------------------------------------------
    // Prepare OMCI Playback LOG PATH 
    // To Save OMCI log here. 
    // ------------------------------------------------------------------
    if(is_omci_log_enable())
    {
        std::string t_time;
        std::array<char, 32> buffer;
        time_t rawtime;
        time(&rawtime);
        const auto timeinfo = localtime(&rawtime);
        strftime(buffer.data(), sizeof(buffer) , "%Y_%m_%dT%H_%M_%S", timeinfo);
        t_time = buffer.data();  

        m_log_out_path="./E_OMCI_LOG/" + t_time + "/";

        if( mkdirp(m_log_out_path.c_str(), DEFAULT_MODE))
        {
            printf("[%s]Create log out path [%s] OK\r\b",__MY_FILE__,  m_log_out_path.c_str());
        }
        else
            printf("[%s]Create log out path [%s] NG\r\b",__MY_FILE__,  m_log_out_path.c_str());
    }
}

BOOL_T OMCI_Parser::omci_parser_validaterxpkt (UI8_T * pkt_p)
{
    return true;
}

BOOL_T OMCI_Parser::check_action_valid(UI16_T Class, UI16_T Action)
{
    return m_me.check_action_valid(Class, Action);
}

BOOL_T OMCI_Parser::check_me_class_valid(UI16_T Class)
{
    return m_me.check_me_s_valid(Class);
}

BOOL_T OMCI_Parser::check_me_instance_valid(UI16_T Class ,UI16_T ME_ID)
{
    return m_me.check_me_o_valid(Class, ME_ID);
}

BOOL_T OMCI_Parser::is_omci_log_enable()
{
    return  m_playback_cfg["RECORD_PLAYBACK"].asBool(); 
}

BOOL_T OMCI_Parser::is_omci_play_enable()
{
    return  m_playback_cfg["PLAYBACK"].asBool(); 
}


BOOL_T OMCI_Parser::me_create_instance(UI16_T TransID ,UI16_T Class ,UI16_T ME_ID, UI8_T *pkt_p,UI8_T pkt_size)
{
    UI8_T  i = 0;
    UI8_T  Action;
    UI16_T Attrs_mask;
    struct timeval tv, tv2;
    unsigned long long start_utime;
    gettimeofday(&tv,NULL);
    start_utime = tv.tv_sec * 1000000 + tv.tv_usec;

    Attrs_mask = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_AttrsMask));
    Action     = (*(pkt_p + OFFSET_OMCI_MSG_TYPE)) & OMCI_MSG_MT_MASK;

    Json::Value omci_s= m_me.get_me_s_json(Class);
    UI8_T raw_data[128] ={0};

    for(i = 0; i < pkt_size ; i++)
    {
        sprintf((char *)&raw_data[2*i],"%02X", *(pkt_p + i));
    }

    printf("[%s]Create me instance Class[%d]Name[%s] instance_id [%d] size[%d] \r\n",\
            __MY_FILE__,Class,omci_s["Name"].asString().c_str() , ME_ID, pkt_size);

    std::string raw((char *)raw_data);
    omci_s["Raw_Data"]       = raw;
    omci_s["TransID"]        = TransID;
    omci_s["Id"]             = ME_ID;
    omci_s["Current_Action"] = get_omci_action_name(Action).c_str();
    omci_s["Create_Time"]    = start_utime;
    //printf("raw data in omci_s[%s]\r\n" , omci_s["Raw_Data"].asString().c_str());
    m_me.create_me_obj(Class, ME_ID, omci_s); 

    /*Chk if need log*/  //Todo , to record all omci pkt //
    if(is_omci_log_enable())
    {
        std::string file_name=std::to_string(TransID)+ "_" + std::to_string(Class)+ "_" + std::to_string(ME_ID) + "_" + omci_s["Name"].asString();
        std::ofstream ofile(m_log_out_path + file_name);
        ofile << omci_s;
        ofile.close();
    }
    return true;
}

BOOL_T OMCI_Parser::me_set_instance(UI16_T TransID ,UI16_T Class ,UI16_T ME_ID, UI8_T *pkt_p,UI8_T pkt_size)
{
    int attrOffset = OFFSET_SET_AttrsValue_START;
    int  attrnum , i;

    std::string tmpClassName  = m_me.get_me_name(Class);

    printf("[%s]me_set_instance Class name[%s] \r\n",__MY_FILE__, tmpClassName);

    ME_S *pTmp = NULL;
    attrnum = m_me.get_attributes_num(Class);

    if(pTmp = m_me.get_me_obj(Class, ME_ID))
    {
        printf("[%s]me_set_instance attrOffset[%d] \r\n",__MY_FILE__, attrOffset);

        for (i = 1; i < attrnum; i++)
        {
            UI16_T tmpAttrSize   = 0;
            UI8_T  tmpAttrFormat = 0;
            tmpAttrFormat        = 4;
            tmpAttrSize          = m_me.get_attributes_size(Class,i); 
            std::string tmpName  = m_me.get_attributes_name(Class,i);

            printf("[%s]me_set_instance attr_id[%d] size[%d]\r\n",__MY_FILE__, i, tmpAttrSize);

            if(1)
            {
                // Check attr support or not
                // Get Attrs mask bit //
                if (tmpAttrFormat == 1)
                {
                    return false;
                }

                if ((tmpAttrFormat == 2) || (tmpAttrFormat == 3))
                {  
                    // memcpy // 
                }
                else
                {  
                    // not-table-string-block attribute_format all use .uint32
                    // memcpy // 
					printf("[%s]Attribute name [%s] attri[%d][0x%04X]\r\n",__MY_FILE__, tmpName.c_str() , i, get_Value_From_Pointer (pkt_p + attrOffset, tmpAttrSize));
                }
                attrOffset += tmpAttrSize;
            }  
        } 
        return true;
    }
    else
    {
        printf("[%s]Error: me_set_instance\r\n",__MY_FILE__);
        return false; 
    }
}

UI16_T OMCI_Parser::get_omci_ui16(UI8_T *data)
{
	return ntohs(*((UI16_T*)data));
}

// ------------------------------------------------------------------
//  1. Get value of size is 4 from pkt.
// ------------------------------------------------------------------
UI32_T  OMCI_Parser::get_Value_From_Pointer(UI8_T *ptr, UI8_T size)
{
	UI32_T sum = 0;
	UI8_T i;
	
	if (size > 4)
		return (sum);

	for (i = 0; i < size; ++i)
	{
		sum = sum * 256 + (*(ptr + i));
	}

    printf("get_Value_From_Pointer sum[0x%04X]\r\n", sum);

	return (sum);
}

std::string OMCI_Parser::get_omci_action_name(UI8_T action_ID)
{
    if (action_ID >= OMCI_ACTIONS_MAX_ID_PLUS_1)
        action_ID = 0;

    std::map<UI8_T, std::string>::const_iterator it ;
    it = g_action_t.find(action_ID);
    return it->second;
}

UI16_T OMCI_Parser::get_omci_action_id(std::string value)
{
    UI16_T key = 0;
    for (auto &i : g_action_t) {
        if (i.second == value) {
            key = i.first;
            break; // to stop searching
        }
    }
    return key;
}

UI16_T OMCI_Parser::omci_pkt_parser(UI8_T *pkt_p, UI8_T pkt_size)
{
    UI8_T  omci_msg_contents[256];
    UI8_T  dPkt[OMCI_PKT_SIZE];
    UI8_T  Action;
    UI16_T Class;
    UI16_T TransID;
    UI16_T ME_ID;
    UI16_T Attrs_mask;
    BOOL_T obj_exist = false; 

    printf("[%s]OMCI_PKT_SIZE is %d\r\n",__MY_FILE__ , OMCI_PKT_SIZE);

    //---------------------------------------------------------------------
    // 1. If input omci packet is invalid, we cannot parse, nor process.
    //---------------------------------------------------------------------
    if(!omci_parser_validaterxpkt(pkt_p))
    {
        return 0;
    }
    memcpy(dPkt, pkt_p, OMCI_PKT_SIZE);
    memset(dPkt + OFFSET_RESP_RESULT, 0, OFFSET_OMCI_TRAILER - OFFSET_RESP_RESULT);
    memcpy(omci_msg_contents, pkt_p + OFFSET_OMCI_MSG_CONTENT, OMCI_MSG_CONTENT_SIZE);

    TransID    = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_TRANS_ID));
    Class      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_CLASS_ID));
    ME_ID      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_ME_ID));
    Attrs_mask = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_AttrsMask));

    //---------------------------------------------------------------------
    // 2. Get MessageType (Action) from input omci packet
    //---------------------------------------------------------------------
    Action = (*(pkt_p + OFFSET_OMCI_MSG_TYPE)) & OMCI_MSG_MT_MASK;
    printf("[%s]class[%d] ME_ID:[%d] Action[%s][0x%04X]\n",__MY_FILE__, Class, ME_ID, get_omci_action_name(Action).c_str(), Action);

    if(ME_ID == 0 && Class != MECID_ONT_DATA) //ONT-DATA 
    {
        printf("[%s]ME INSTANCE ID CAN'T BE 0 !!!!\r\n", __MY_FILE__);
        return 0;
    }

    // Always igore notifications like: AVC from OLT. Alarm from OLT.
    if ((Action == MSGTYPE_ATTRIBUTE_VALUE_CHANGE) || (Action == MSGTYPE_ALARM))
    {
        printf("[%s]MSGTYPE_ATTRIBUTE_VALUE_CHANGE MSGTYPE_ALARM!!!\r\n", __MY_FILE__);
        //return 0;
    }

    if ((Action == MSGTYPE_SET) || (Action == MSGTYPE_GET) || (Action == MSGTYPE_GET_CURRENT_DATA))
    {
        printf("[%s]attr_mask: %04X\n", __MY_FILE__, Attrs_mask);
    }

    //---------------------------------------------------------------------
    // 3. Check has this me from ME_S. 
    //---------------------------------------------------------------------

    if (!check_me_class_valid(Class))
    {
        printf("[%s]NOT Supported ME (%d) .Please check if impliment me skeleton\n",__MY_FILE__, Class);
        return 0; 
    }
    else
    {
        // Check action exist for this ME //
        if( !check_action_valid(Class, Action) )
        {
            printf("[%s]ME[%d] not support this action[%d]!!\r\n",__MY_FILE__, Class, Action);
            return 0; 
        }
        else
            printf("[%s]Support this Action!\r\n",__MY_FILE__);


        obj_exist = check_me_instance_valid(Class ,ME_ID);

        if (!obj_exist && (Action != MSGTYPE_CREATE)&& (Class != MECID_T_CONT)) //Todo , add exclusive class function to chk
        {
            printf("[%s]ME CLass[%d] instance_ID NOT exist. cannot [%s]\n",__MY_FILE__, Class, get_omci_action_name(Action).c_str());
            return 0; 
        }
        else if(obj_exist)
        {
            printf("[%s]ME [%d] instance found. Prepare %s \n",__MY_FILE__ ,Class, get_omci_action_name(Action).c_str());
        }  
    }  

    //---------------------------------------------------------------------
    // 4  Take related action according to Action(MessageType), in switch-block
    //---------------------------------------------------------------------

    switch (Action)
    {
        case MSGTYPE_CREATE:
            if (obj_exist)
            {
                printf("[%s]ME_class(%d), ME instance(%d) exist, cannot create again\n",__MY_FILE__ ,Class, ME_ID);
            }
            else
                me_create_instance(TransID, Class , ME_ID, pkt_p, pkt_size);

            if (Class == MECID_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("[%s]VTOCD tpe!!!!!!\r\n", __MY_FILE__);
            }
            else if (Class == MECID_EXT_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("[%s]E-VTOCD tpe!!!!!!\r\n", __MY_FILE__);
            }
        case MSGTYPE_SET:

            /*T-CONT createed in ONT it self*/
            if (Class == MECID_T_CONT)
            {
                printf("[%s]T_CONT CREATE/MSGTYPE_SET!!!!!!\r\n", __MY_FILE__);
                me_create_instance(TransID, Class , ME_ID, pkt_p, pkt_size);
            }

            if(me_set_instance(TransID, Class , ME_ID, pkt_p, pkt_size))
                printf("[%s]MSGTYPE_SET OK !!!!!!\r\n", __MY_FILE__);
            else
                printf("[%s]MSGTYPE_SET NG !!!!!!\r\n", __MY_FILE__);

            break;


        case MSGTYPE_DELETE:
            printf("[%s]MSGTYPE_DELETE!!!!!!\r\n", __MY_FILE__);
            break;

        case MSGTYPE_GET:
        case MSGTYPE_GET_CURRENT_DATA:
            printf("[%s]MSGTYPE_GET!!!!!!\r\n", __MY_FILE__);
            break;

        case MSGTYPE_GET_NEXT:
            printf("[%s]MSGTYPE_GET_NEXT!!!!!!\r\n",__MY_FILE__);
            break;

            //-----------------------------------------------------------------
            // Parser prepare msg_content field.
            // ME_ont_data.c will do all for
            //   MIB_RESET, GET_ALL_ALARMS, GET_ALL_ALARMS_NEXT,
            //   MIB_UPLOAD, MIB_UPLOAD_NEXT
            //-----------------------------------------------------------------
            //		//-----------------------------------------------------------------
		case MSGTYPE_MIB_RESET:
            me_create_instance(TransID, Class , ME_ID, pkt_p, pkt_size);
            printf("[%s]MSGTYPE_REBOOT!!!!!!\r\n",__MY_FILE__);
            break;
		case MSGTYPE_GET_ALL_ALARMS:
		case MSGTYPE_GET_ALL_ALARMS_NEXT:
		case MSGTYPE_MIB_UPLOAD:
		case MSGTYPE_MIB_UPLOAD_NEXT:
		//-----------------------------------------------------------------
		// MSGTYPE_TEST is not tested yet,
		// because different ME_classes have their own packet format.
		//-----------------------------------------------------------------
		case MSGTYPE_TEST:
		//-----------------------------------------------------------------
		// Parser prepare msg_content field.
		// ME_software_image.c will do all for
		//   START_SOFTWARE_DOWNLOAD, DOWNLOAD_SECTION,
		//   END_SOFTWARE_DOWNLOAD, ACTIVATE_SOFTWARE, COMMIT_SOFTWARE
		//-----------------------------------------------------------------
		case MSGTYPE_START_SOFTWARE_DOWNLOAD:
		case MSGTYPE_DOWNLOAD_SECTION:
		case MSGTYPE_END_SOFTWARE_DOWNLOAD:
		case MSGTYPE_ACTIVATE_SOFTWARE:
		case MSGTYPE_COMMIT_SOFTWARE:
		//-----------------------------------------------------------------
		// Parser prepare msg_content field.
		// ME_ont_g.c will do all for
		//   SYNCHRONIZE_TIME, REBOOT
		//-----------------------------------------------------------------
		case MSGTYPE_SYNCHRONIZE_TIME:

        case MSGTYPE_REBOOT:
            printf("[%s]MSGTYPE_REBOOT!!!!!!\r\n",__MY_FILE__);
            break;

            //-----------------------------------------------------------------
            // AK==0 MSGTYPE done by Parser_send_notification_to_OLT.
            // OLT should NOT send such MsgType, so we do nothing here.
            //-----------------------------------------------------------------
        case MSGTYPE_ALARM:	/*AK=0 */
        case MSGTYPE_ATTRIBUTE_VALUE_CHANGE:	/*AK=0 */
        case MSGTYPE_TEST_RESULT:	/*AK=0 */
            break;

        default:
            printf("[%s]Illegal message Type : %d", __MY_FILE__, Action);
    }  // switch (Action)
    return 0;
}
