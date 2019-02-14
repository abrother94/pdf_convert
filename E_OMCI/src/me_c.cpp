#include <iostream>
#include <fstream>
#include <istream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <typeinfo>
#include <all_me.hpp>
#include <me_c.hpp>
#include <omci_parser.hpp>

ME_C::ME_C()
{
    if(get_omci_s())
    {
        printf("[%s]get_omci_s OK!!\r\n",__MY_FILE__);
        if(!pre_create_me_obj())
            printf("[%s]pre_create_me_obj NG!!\r\n",__MY_FILE__);
    }
    else
    {
        printf("[%s]get_omci_s NG!!\r\n", __MY_FILE__);
        printf("[%s]###### SUPPORTED ME FILE ERROR #######!!!!\r\n", __MY_FILE__);
    }
}

ME_C::~ME_C()
{
    release_all_me_obj();
}

// ------------------------------------------------------------------
// 1.ME create by ONT
//   MECID_ONT_DATA
//   MECID_PPTP_ETHERNET_UNI
// ------------------------------------------------------------------


BOOL_T ME_C::pre_create_me_obj()
{
    BOOL_T res=false;
    Json::Value Tvalue;
    /*ONT_DATA*/
    printf("[%s]pre_create_me_obj ONT_DATA\r\n", __MY_FILE__);
    Tvalue = get_me_s_json(MECID_ONT_DATA);
    res = create_me_obj(MECID_ONT_DATA, 0, Tvalue);

    return res;
}

void ME_C::release_all_me_obj()
{
    std::map < std::pair<int,int>, ME_S *>::iterator it;
    for(auto it = M_OMCI_P.begin(); it != M_OMCI_P.end(); ++it) 
    {
        ME_S * pME_S = it->second;
        if(pME_S)
        {
            delete pME_S;
        }
    }
    M_OMCI_P.clear();
}

ME_S * ME_C::get_me_obj(int class_id, int instance_id)
{
    ME_S *pTmp = NULL;
    pTmp =  M_OMCI_P[std::make_pair(class_id, instance_id)]; 
    if(!pTmp)
        return NULL;
    else
        return pTmp; 
}

// ------------------------------------------------------------------
// 1. Add SWITCHCASE( XXX_CID, instance_id, XXX_ME_NAME) after you 
//    use create_me_cpp.sh to create a new ME. 
// ------------------------------------------------------------------

BOOL_T ME_C::create_me_obj(int class_id, int instance_id, Json::Value me_s)
{
    ME_S *pME = NULL;

    printf("[%s]Create me object class id [%d] instance id[%d] \r\n", __MY_FILE__, class_id, instance_id);

    pME = M_OMCI_P[std::make_pair(class_id, instance_id)];
    if (pME == NULL)
    {
        switch(class_id)
        {
            //ADDHERE
            SWITCHCASE(47 , instance_id, ME_MAC_bridge_port_configuration_data, me_s);
            SWITCHCASE(11 , instance_id, ME_Physical_path_termination_point_Ethernet_UNI, me_s);
            SWITCHCASE(84 , instance_id, ME_VLAN_tagging_filter_data, me_s);
            SWITCHCASE(46 , instance_id, ME_MAC_bridge_configuration_data, me_s);
            SWITCHCASE(268 , instance_id, ME_GEM_port_network_CTP, me_s);
            SWITCHCASE(45 , instance_id, ME_MAC_bridge_service_profile, me_s);
            SWITCHCASE(266 , instance_id, ME_GEM_interworking_termination_point, me_s);
            SWITCHCASE(310 , instance_id, ME_Multicast_subscriber_config_info, me_s);
            SWITCHCASE(262 , instance_id, ME_T_CONT, me_s);
            SWITCHCASE(309 , instance_id, ME_Multicast_operations_profile, me_s);
            SWITCHCASE(171 , instance_id, ME_Extended_VLAN_tagging_operation_configuration_data, me_s);
            SWITCHCASE(2 , instance_id, ME_ONT_data, me_s);
            SWITCHCASE(130 , instance_id, ME_802_1p_mapper_service_profile, me_s);
            SWITCHCASE(281 , instance_id, ME_Multicast_GEM_interworking_termination_point, me_s);
            SWITCHCASE(272 , instance_id, ME_GAL_Ethernet_profile, me_s);
            default:
                break;
        }
        return true;
    }
    else
    {
        printf("[%s]Already exist class_id [%d] instance_id[%d]!!\r\n", __MY_FILE__, class_id, instance_id);
        return false;
    }
}


// ------------------------------------------------------------------
// 1. Collect supported ME info in S_ME/
// ------------------------------------------------------------------

BOOL_T ME_C::get_omci_s()
{
    std::string ME_S_DIR(ME_SEC_PATH);
    struct dirent *entry;

    DIR *dir = opendir(ME_S_DIR.c_str());

    if (dir == NULL) 
    {
        printf("[%s]no such path exist!!\r\n", __MY_FILE__);
        return false;
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string dot(".");
        std::string ddot("..");

        std::string tmp_me_name = entry->d_name;

        if((dot == tmp_me_name) || (ddot == tmp_me_name))
            continue;

        std::string tmp_me_cid = tmp_me_name.substr(0, tmp_me_name.find("_"));
        printf("[%s]me name[%s] me cid[%s]\r\n", __MY_FILE__, tmp_me_name.c_str(), tmp_me_cid.c_str());

        std::string m_config_file_path = ME_S_DIR + tmp_me_name ;
        printf("[%s]new pathname[%s]\r\n",__MY_FILE__,  m_config_file_path.c_str());

        ifstream    m_source_files= {};

        m_source_files.open(m_config_file_path);

        if(m_source_files.good())
        {   
            Json::Value omci_s;
            Json::Reader reader;
            BOOL_T isJsonOK = (reader.parse(m_source_files, omci_s));

            if(isJsonOK)
            {
                printf("[%s]Get omci_s ok \r\n", __MY_FILE__);
                printf("[%s]Class id:%d\r\n", __MY_FILE__, omci_s["Class"].asInt());
                int Class =  omci_s["Class"].asInt();
                int Id = 0; 
                M_OMCI_G[std::make_pair(Class,Id)]=omci_s; 
                printf("[%s]g vecotr size is %zu\r\n",__MY_FILE__ ,M_OMCI_G.size());
            }
            else
            {
                printf("[%s]Get omci_s ng\r\n", __MY_FILE__);
                return false;
            }
        }
        else
        {
            printf("[%s]Open file NG\r\n", __MY_FILE__);
            return false;
        }
    }

    closedir(dir);
    return true;
}

Json::Value  ME_C::get_me_s_json(UI16_T Class)
{
    Json::Value Tvalue;
    std::map<std::pair<int,int>, Json::Value>::const_iterator it;
    it = M_OMCI_G.find(std::make_pair(Class, 0));

    if (it == M_OMCI_G.end()) 
    {
        return Tvalue;
    }
    else
    {
        Tvalue = it->second;
        return Tvalue;
    }
}


BOOL_T ME_C::check_me_s_valid(UI16_T Class)
{
    std::map<std::pair<int,int>, Json::Value>::const_iterator it;
    it = M_OMCI_G.find(std::make_pair(Class, 0));

    if (it == M_OMCI_G.end()) 
        return false;
    else 
        return true;
}

BOOL_T ME_C::check_me_o_valid(UI16_T Class, UI16_T instance_id)
{
    printf("[%s]check_me_o_valid Class[%d] instance_id[%d]\r\n",__MY_FILE__ ,Class, instance_id);
    std::map<std::pair<int,int>, ME_S *>::const_iterator it;
    it = M_OMCI_P.find(std::make_pair(Class, instance_id));

    if (it == M_OMCI_P.end()) 
        return false;
    else 
        return true;
}

UI16_T ME_C::get_attributes_size(UI16_T Class,UI16_T attr_id)
{
    Json::Value omci_s;
    omci_s = M_OMCI_G[std::make_pair(Class, 0)]; 

    std::string astring = omci_s["Attrs_info"][attr_id -1]["Size"].asString();

    return std::stoi(astring);
}

std::string ME_C::get_attributes_name(UI16_T Class,UI16_T attr_id)
{
    Json::Value omci_s;
    omci_s = M_OMCI_G[std::make_pair(Class, 0)]; 

    std::string astring = omci_s["Attrs_info"][attr_id -1]["Name"].asString();

    return astring;
}

UI16_T ME_C::get_attributes_num(UI16_T Class)
{
    Json::Value omci_s;
    omci_s = M_OMCI_G[std::make_pair(Class, 0)]; 

    return omci_s["Attrs_info"].size();
}

std::string ME_C::get_me_name(UI16_T Class)
{
    Json::Value omci_s;
    omci_s = M_OMCI_G[std::make_pair(Class, 0)]; 

    return omci_s["Name"].asString();
}

BOOL_T ME_C::check_action_valid(UI16_T Class, UI16_T Action)
{
    Json::Value omci_s;

    omci_s = M_OMCI_G[std::make_pair(Class, 0)]; 

    std::string action= omci_s["Supported_Action"].asString();
    std::string in_action = OMCI_Parser::get_omci_action_name(Action);

    printf("[%s]Class[%d] chk action[%s][%d] support action[%s][%d]\r\n",__MY_FILE__ , \
    Class, in_action.c_str(),Action, action.c_str(), OMCI_Parser::get_omci_action_id("SET"));

    if(action.find("create") != std::string::npos && (Action == OMCI_Parser::get_omci_action_id("CREATE")))
    {
        return true;
    }
    if(action.find("delete")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("DELETE")))
    {
        return true;
    }
    if(action.find("get")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("GET")))
    {
        return true;
    }
    if(action.find("set")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("SET")))
    {
        return true;
    }
    if(action.find("reboot")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("SET")))
    {
        return true;
    }
    if(action.find("mib reset")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("MIB_RESET")))
    {
        return true;
    }
    if(action.find("alarm")!= std::string::npos && (Action == OMCI_Parser::get_omci_action_id("ALARM")))
    {
        return true;
    }

    return false;
}

void ME_C::show_all_me_obj()
{
    std::map < std::pair<int,int>, ME_S *>::iterator it;

    printf("\r\n");

    for(auto it = M_OMCI_P.begin(); it != M_OMCI_P.end(); ++it) 
    {
        int i;
        ME_S * pME_S = it->second;
        Json::Value tmp_omci_s =   pME_S->get_j_me();
        UI8_T attrnum = tmp_omci_s["Attrs_info"].size(); 

        printf("\r\n\r\n");
        printf("ME NAME[%s] INS_ID[%d] \r\n", tmp_omci_s["Name"].asString().c_str(), tmp_omci_s["Id"].asInt());

        for(i = 0; i < attrnum; i++)
        {
            printf("    Attribute[%d] Name[%s] Value[%s]\r\n", i+1, tmp_omci_s["Attrs_info"][i]["Name"].asString().c_str(), tmp_omci_s["Attrs_info"][i]["Value"].asString().c_str() );
        }
    }
    printf("\r\n\r\n");
}


