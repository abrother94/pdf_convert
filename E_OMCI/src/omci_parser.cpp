#include <omci_parser.hpp>
#include <common.hpp>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

using namespace std;

BOOL_T OMCI_Parser::omci_parser_validaterxpkt (UI8_T * pkt_p)
{
    return true;
}

BOOL_T OMCI_Parser::check_action_valid(UI16_T Class, UI16_T Action)
{
    return m_me.check_action_valid(Class, Action);
}

BOOL_T OMCI_Parser::get_me_by_class(UI16_T Class)
{
    return m_me.check_me_s_valid(Class);
}

BOOL_T OMCI_Parser::me_find_instance(UI16_T Class ,UI16_T ME_ID)
{
    return m_me.check_me_o_valid(Class, ME_ID);
}

BOOL_T OMCI_Parser::me_create_instance(UI16_T Class ,UI16_T ME_ID)
{
    printf("[%s]Create me instance [%d] instance_id [%d]\r\n",__MY_FILE__,Class, ME_ID);
    Json::Value omci_s= m_me.get_me_s_json(Class);
    m_me.create_me_obj(Class, ME_ID, omci_s); 
    return true;
}


UI16_T OMCI_Parser::get_omci_ui16(UI8_T *data)
{
	return ntohs(*((UI16_T*)data));
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

UI16_T OMCI_Parser::omci_pkt_parser(UI8_T *pkt_p)
{
    UI8_T  omci_msg_contents[256];
    UI8_T  dPkt[OMCI_PKT_SIZE];
    UI8_T  Action;
    UI16_T Class;
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

    Class      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_CLASS_ID));
    ME_ID      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_ME_ID));
    Attrs_mask = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_AttrsMask));

    //---------------------------------------------------------------------
    // 2. Get MessageType (Action) from input omci packet
    //---------------------------------------------------------------------
    Action = (*(pkt_p + OFFSET_OMCI_MSG_TYPE)) & OMCI_MSG_MT_MASK;
    printf("[%s]class[%d]  ME_ID:[%d]  Action[%s] [0x%04X]\n",__MY_FILE__, Class, ME_ID, get_omci_action_name(Action).c_str(), Action);
    if(ME_ID == 0)
    {
        printf("[%s]ME INSTANCE ID CAN'T BE 0 !!!!\r\n", __MY_FILE__);
        return 0;
    }


    // Always igore notifications like: AVC from OLT. Alarm from OLT.
    if ((Action == MSGTYPE_ATTRIBUTE_VALUE_CHANGE) || (Action == MSGTYPE_ALARM))
    {
        printf("[%s]MSGTYPE_ATTRIBUTE_VALUE_CHANGE MSGTYPE_ALARM!!!\r\n", __MY_FILE__);
        return 0;
    }

    if ((Action == MSGTYPE_SET) || (Action == MSGTYPE_GET) || (Action == MSGTYPE_GET_CURRENT_DATA))
    {
        printf("[%s]attr_mask: %04X\n", __MY_FILE__, Attrs_mask);
    }

    // Check action exist for this ME //
    if( !check_action_valid(Class, Action) )
    {
        printf("[%s]ME[%d] not support this action[%d]!!\r\n",__MY_FILE__, Class, Action);
        return 0; 
    }
    else
        printf("[%s]Support this Action!\r\n",__MY_FILE__);

    //---------------------------------------------------------------------
    // 3. Check has this me from ME_S. 
    //---------------------------------------------------------------------

    if (!get_me_by_class(Class))
    {
        printf("[%s]NOT Supported ME (%d)\n",__MY_FILE__, Class);
        return 0; 
    }
    else
    {
        obj_exist = me_find_instance(Class ,ME_ID);
        if (!obj_exist && (Action != MSGTYPE_CREATE))
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
                me_create_instance(Class , ME_ID);

            if (Class == MECID_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("[%s]VTOCD tpe!!!!!!\r\n", __MY_FILE__);
            }
            else if (Class == MECID_EXT_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("[%s]E-VTOCD tpe!!!!!!\r\n", __MY_FILE__);
            }
            break;

        case MSGTYPE_DELETE:
            printf("[%s]MSGTYPE_DELETE!!!!!!\r\n", __MY_FILE__);
            break;

        case MSGTYPE_SET:
            printf("[%s]MSGTYPE_SET!!!!!!\r\n", __MY_FILE__);
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
