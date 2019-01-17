#include <omci_parser.hpp>
#include <common.hpp>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

bool omci_parser_validaterxpkt (UI8_T * pkt_p)
{
    return true;
}
bool get_me_by_class(UI16_T Class)
{
    return true;
}

bool me_find_instance (UI16_T Class ,UI16_T ME_ID)
{
    return true;
}

bool me_create_instance(UI16_T Class ,UI16_T ME_ID, UI8_T * pkt_p)
{
    return true;
}


inline UI16_T get_omci_ui16(UI8_T *data)
{
	return ntohs(*((UI16_T*)data));
}

inline char* get_omci_action_name(UI8_T action_ID)
{
    if (action_ID >= OMCI_ACTIONS_MAX_ID_PLUS_1)
        action_ID = 0;
    return OMCI_Actions_name[action_ID];
}

int omci_pkt_parser(UI8_T *pkt_p, int queue)
{
    UI8_T OMCI_msg_contents[256];
    UI8_T dPkt[OMCI_PKT_SIZE];
    UI8_T Action, tmp;
    UI8_T responseReady = 0;
    UI16_T Class;
    UI16_T ME_ID;
    UI16_T Attrs_mask;
    UI32_T size;
    BOOL_T obj_exist = false; 

    //---------------------------------------------------------------------
    // 1. If input omci packet is invalid, we cannot parse, nor process.
    //---------------------------------------------------------------------
    if (omci_parser_validaterxpkt (pkt_p))
    {
        return -1;
    }
    memcpy(dPkt, pkt_p, OMCI_PKT_SIZE);
    memset(dPkt + OFFSET_RESP_RESULT, 0, OFFSET_OMCI_TRAILER - OFFSET_RESP_RESULT);
    memcpy(OMCI_msg_contents, pkt_p + OFFSET_OMCI_MSG_CONTENT, OMCI_MSG_CONTENT_SIZE);

    Class      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_CLASS_ID));
    ME_ID      = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_OMCI_ME_ID));
    Attrs_mask = get_omci_ui16((UI8_T *) (pkt_p + OFFSET_AttrsMask));

    //---------------------------------------------------------------------
    // 2. Get MessageType (Action) from input omci packet
    //---------------------------------------------------------------------
    Action = (*(pkt_p + OFFSET_OMCI_MSG_TYPE)) & OMCI_MSG_MT_MASK;
    printf("PARSER: class[%d]  ME_ID:[%d]  Action[%s] [0x%04X]\n", Class, ME_ID, get_omci_action_name(Action), Action);

    // Always igore notifications like: AVC from OLT. Alarm from OLT.
    if ((Action == MSGTYPE_ATTRIBUTE_VALUE_CHANGE) || (Action == MSGTYPE_ALARM))
    {
        printf("MSGTYPE_ATTRIBUTE_VALUE_CHANGE MSGTYPE_ALARM!!!\r\n");
        return 0;
    }

    if ((Action == MSGTYPE_SET) || (Action == MSGTYPE_GET) || (Action == MSGTYPE_GET_CURRENT_DATA))
    {
        printf("attr_mask: %04X\n", Attrs_mask);
    }

    //---------------------------------------------------------------------
    // 3. Check has this me from ME_S. 
    //---------------------------------------------------------------------

    if (get_me_by_class(Class))
    {
        printf("NOT Supported ME (%d)\n",Class);
    }
    else
    {
        obj_exist = me_find_instance(Class ,ME_ID);
        if (!obj_exist && (Action != MSGTYPE_CREATE))
        {
            printf("ME ERR: ME CLass[%d] instance_ID NOT exist. cannot [%s]\n", Class, get_omci_action_name (Action));
        }
        else
        {
            // Check action is support or not //
            //if (!((pME->Actions_table) & (1 << Action)))
            {
                printf("ME ERR: ME CLass[%d] Not support Action [%s]\n", Class, get_omci_action_name (Action));
            }
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
                printf("ME ERR: ME_class(%d), ME instance(%d) exist, cannot create again\n", Class, ME_ID);
            }
            else
                me_create_instance(Class , ME_ID, pkt_p);

            if (Class == MECID_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("VTOCD tpe!!!!!!\r\n");
            }
            else if (Class == MECID_EXT_VLAN_TAGGING_OP_CONFIG_DATA)
            {
                printf("E-VTOCD tpe!!!!!!\r\n");
            }
            break;

        case MSGTYPE_DELETE:
            printf("MSGTYPE_DELETE!!!!!!\r\n");
            break;

        case MSGTYPE_SET:
            printf("MSGTYPE_SET!!!!!!\r\n");
            break;

        case MSGTYPE_GET:
        case MSGTYPE_GET_CURRENT_DATA:
            printf("MSGTYPE_GET!!!!!!\r\n");
            break;

        case MSGTYPE_GET_NEXT:
            printf("MSGTYPE_GET_NEXT!!!!!!\r\n");
            break;

            //-----------------------------------------------------------------
            // Parser prepare msg_content field.
            // ME_ont_data.c will do all for
            //   MIB_RESET, GET_ALL_ALARMS, GET_ALL_ALARMS_NEXT,
            //   MIB_UPLOAD, MIB_UPLOAD_NEXT
            //-----------------------------------------------------------------
        case MSGTYPE_REBOOT:
            printf("MSGTYPE_REBOOT!!!!!!\r\n");
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
            printf("ME ERR: illegal message Type : %d", Action);
    }  // switch (Action)
    return 0;
}
