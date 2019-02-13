#if !defined(PARSER_HPP_INCLUDED)
#define PARSER_HPP_INCLUDED

#include <common.hpp>
#include <string> 
#include <map>
#include <me_c.hpp>
#include <time.h>

using namespace std;

enum OMCI_ME_CLASS_ID_E
{
	// ----------------------------------------------
	// List of G.984.4 ME Class values supported:
	// ----------------------------------------------
	MECID_ONT_DATA									= 2,   // 9.1.3
	MECID_CARDHOLDER /* Subscriber Line Cardholder*/= 5,   // 9.1.5
	MECID_CIRCUIT_PACK	/* Subscriber Line Card */	= 6,   // 9.1.6
	MECID_SOFTWARE_IMAGE							= 7,   // 9.1.4
	MECID_PPTP_ETHERNET_UNI							= 11,  // 9.5.1
	MECID_ETH_PM_HISTORY_DATA						= 24,  // 9.5.2
	MECID_MAC_BRIDGE_SERVICE_PROFILE				= 45,  // 9.3.1
	MECID_MAC_BR_CFGDATA							= 46,  // 9.3.2 for RSTP
	MECID_MAC_BRIDGE_PORT_CONFIG_DATA				= 47,  // 9.3.4
	MECID_MAC_BR_PORT_DSGDATA						= 48,  // 9.3.5 for RSTP
	MECID_MAC_BR_PORT_FILTER_TABLE_DATA				= 49,  // 9.3.6
	MECID_MAC_BR_PORT_BRIDGE_TABLE_DATA				= 50,  // 9.3.8
	MECID_MAC_BRG_PM_HISTORY_DATA					= 52,  // 9.3.9
	MECID_VLAN_TAGGING_OP_CONFIG_DATA				= 78,  // 9.3.12
	MECID_VLAN_TAGGING_FILTER_DATA					= 84,  // 9.3.11
	MECID_ETH_PM_HISTORY_DATA2						= 89,  // 9.5.3
	MECID_I8021P_MAPPER_SERVICE_PROFILE				= 130, // 9.3.10
	MECID_OLT_G										= 131, // 9.12.2
	MECID_ONT_POWER_SHEDDING						= 133, // 9.1.7
	MECID_IP_HOST_CONFIG_DATA						= 134, // 9.4.12
	MECID_EXT_VLAN_TAGGING_OP_CONFIG_DATA			= 171, // 9.3.13
	MECID_ONT_SYS_MGMT								= 240, // DASAN/Tellion Private ME
	MECID_ACS_VENDOR_SPECIFIC						= 242, // CORECESS Private ME 2011/8/8
	MECID_PROTOCOL_BASED_VLAN_TAGGING_OP_DATA		= 245, // CORECESS Private ME 2011/4/7
	MECID_ONT_G										= 256, // 9.1.1
	MECID_ONT2_G									= 257, // 9.1.2
	MECID_T_CONT									= 262, // 9.2.2
	MECID_ANI_G										= 263, // 9.2.1
	MECID_UNI_G										= 264, // 9.12.1
	MECID_GEM_INTER_TERMINATION_POINT				= 266, // 9.2.4
	MECID_GEM_PORT_PM_HISTORY_DATA					= 267, // 9.2.6
	MECID_GEM_PORT_NETWORK_CTP						= 268, // 9.2.3
	MECID_GAL_ETH_PROFILE							= 272, // 9.2.7
	MECID_THRESHLD_DATA_1							= 273, // 9.12.6
	MECID_THRESHLD_DATA_2							= 274, // 9.12.7
	MECID_PRIORITY_QUEUE_G							= 277, // 9.11.1
	MECID_TRAFFIC_SCHEDULER_G						= 278, // 9.11.2
	MECID_GEM_TRAFFIC_DESCRIPTOR					= 280, // 9.11.3
	MECID_MULTICAST_GEM_INTERWORK_TERM_POINT		= 281, // 9.2.5
	MECID_DOT1X_PORT_EXT_PKG						= 290, // 9.3.14
	MECID_DOT1X_CFG_PROF							= 291, // 9.3.15
	MECID_DOT1X_PM_HISTORY_DATA						= 292, // 9.3.16
	MECID_RADIUS_PM_HISTORY_DATA					= 293, // 9.3.17
	MECID_ETH_PM_HISTORY_DATA3						= 296, // 9.5.4
	MECID_DOT1AG_MAINTENANCE_DOMAIN					= 299, // 9.3.19
	MECID_DOT1AG_MAINTENANCE_ASSOCIATION			= 300, // 9.3.20
	MECID_DOT1AG_MEP								= 302, // 9.3.22
	MECID_MULTICAST_OPERATION_PROFILE				= 309, // 9.3.27
	MECID_MULTICAST_SUBSCRIBER_CONFIG_INFO			= 310, // 9.3.28
	MECID_MULTICAST_SUB_MONITOR						= 311, // 9.3.29
	// ----------------------------------------------
	// VoIP MEs:
	// ----------------------------------------------
	MECID_PPTP_POTS_UNI								= 53,  // 9.9.1
	MECID_VOICE_SERVICE_PROF						= 58,  // 9.9.6
	MECID_TCPUDP_CFGDATA							= 136, // 9.4.14
	MECID_NETWORK_ADDR								= 137, // 9.12.3
	MECID_VOIP_CFGDATA								= 138, // 9.9.18
	MECID_VOIP_VOICE_CTP							= 139, // 9.9.4
	MECID_VOIP_LINE_STATUS							= 141, // 9.9.11
	MECID_VOIP_MEDIA_PROF							= 142, // 9.9.5
	MECID_RTP_PROF									= 143, // 9.9.7
	MECID_NET_DIAL_PLAN_TABLE						= 145, // 9.9.10
	MECID_VOIP_APPL_SERVICE_PROF					= 146, // 9.9.8
	MECID_VOIP_FEAT_ACC_CODES						= 147, // 9.9.9
	MECID_AUTHENT_SECURITY_METH						= 148, // 9.12.4
	MECID_SIP_AGENT_CFGDATA							= 150, // 9.9.3
	MECID_SIP_USER_DATA								= 153, // 9.9.2
	MECID_LARGE_STRING								= 157, // 9.12.5
	// ----------------------------------------------
	MECID_ETH_FRAME_PM_HISTORY_DATA_DOWNSTREAM		= 321, // 9.3.30 (Amd-2)
	MECID_ETH_FRAME_PM_HISTORY_DATA_UPSTREAM		= 322, // 9.3.31 (Amd-2)
	MECID_VIRTUAL_ETHER_INF_POINT					= 329, // 9.5.5  (Amd-2)
	MECID_GENERIC_STATUS_PORTAL						= 330, // 9.12.14 (Amd-2)
	MECID_ETH_PM_HISTORY_DATA4						= 351, // 9.X.Y (Huawei Proprietary)
	MECID_G9844_SPEC_CLASS_VALUE_LAST_PLUS_1,		       // [323] Comply ALU's MEs list
	// ----------------------------------------------
	// Following are ALU's Proprietary MEs:
	// ----------------------------------------------
	MECID_ALU_PROPRIETARY_CLASS_VALUE_FIRST			= 65281, // WARNING .. Hard-coded !!
	MECID_ONT_AGGREGATE_GEM_PORT_PM_HISTORY_DATA	= 65281, // ALU MIB spec
	MECID_ETH_TRAFFIC_PM_HISTORY_DATA				= 65282, // ALU MIB spec
	MECID_NTP_CONFIG								= 65288, // ALU MIB spec 3.1.41
	MECID_VoIP_Client_1								= 65291, // ALU voip spec 3.1.10
	MECID_VoIP_Supplemental_1						= 65292, // ALU voip spec 3.1.11
	MECID_VoIP_Client_2								= 65293, // ALU voip spec 3.1.12
	MECID_ONT_GENERIC_V2							= 65296, // ALU MIB spec
	MECID_UNI_SUPPLEMENTAL_1_V2						= 65297, // ALU MIB spec
	MECID_GEM_PORT_PM_HISTORY_DATA_PART_2			= 65300, // ALU undefined
	MECID_IPMACVLAN_ANTI_SPOOF_LIST_V2				= 65301, // ALU MIB spec
	MECID_NTP_CONFIG_V2								= 65304, // ALU MIB spec 3.1.47
	MECID_ALU_PROPRIETARY_CLASS_VALUE_LAST_PLUS_1,	         // Comply ALU's MEs list
	// ----------------------------------------------
	ME_G9844_SPEC_MAX_COUNT		= ( MECID_G9844_SPEC_CLASS_VALUE_LAST_PLUS_1 ),
	ME_ALU_PROPRIETARY_MAX_COUNT= ( MECID_ALU_PROPRIETARY_CLASS_VALUE_LAST_PLUS_1 -
									MECID_ALU_PROPRIETARY_CLASS_VALUE_FIRST ),
};

enum OMCI_MESSAGE_TYPE_E
{
	MSGTYPE_CREATE					= 4,
	MSGTYPE_DELETE					= 6,
	MSGTYPE_SET						= 8,
	MSGTYPE_GET						= 9,
	MSGTYPE_GET_ALL_ALARMS			= 11,
	MSGTYPE_GET_ALL_ALARMS_NEXT		= 12,
	MSGTYPE_MIB_UPLOAD				= 13,
	MSGTYPE_MIB_UPLOAD_NEXT			= 14,
	MSGTYPE_MIB_RESET				= 15,
	MSGTYPE_ALARM					= 16,
	MSGTYPE_ATTRIBUTE_VALUE_CHANGE	= 17,
	MSGTYPE_TEST					= 18,
	MSGTYPE_START_SOFTWARE_DOWNLOAD	= 19,
	MSGTYPE_DOWNLOAD_SECTION		= 20,
	MSGTYPE_END_SOFTWARE_DOWNLOAD	= 21,
	MSGTYPE_ACTIVATE_SOFTWARE		= 22,
	MSGTYPE_COMMIT_SOFTWARE			= 23,
	MSGTYPE_SYNCHRONIZE_TIME		= 24,
	MSGTYPE_REBOOT					= 25,
	MSGTYPE_GET_NEXT				= 26,
	MSGTYPE_TEST_RESULT				= 27,
	MSGTYPE_GET_CURRENT_DATA		= 28,
	MSGTYPE_SET_ALU_NO_DATASYNC		= 29,
	OMCI_ACTIONS_MAX_ID_PLUS_1,
	MSGTYPE_MT_MASK					= 0x1F,
};

constexpr UI8_T OMCI_MSG_DB_MASK    = 0x80;
constexpr UI8_T OMCI_MSG_AR_MASK    = 0x40;
constexpr UI8_T OMCI_MSG_AK_MASK    = 0x20;
constexpr UI8_T OMCI_MSG_MT_MASK    = 0x1F;

constexpr UI8_T OFFSET_OMCI_TRANS_ID     = 0;
constexpr UI8_T OFFSET_OMCI_MSG_TYPE     = (OFFSET_OMCI_TRANS_ID +2);
constexpr UI8_T OFFSET_OMCI_DEV_ID       = (OFFSET_OMCI_MSG_TYPE +1);
constexpr UI8_T OFFSET_OMCI_CLASS_ID     = (OFFSET_OMCI_DEV_ID +1);
constexpr UI8_T OFFSET_OMCI_ME_ID        = (OFFSET_OMCI_CLASS_ID +2);
constexpr UI8_T OFFSET_OMCI_MSG_CONTENT  = (OFFSET_OMCI_ME_ID +2);
constexpr UI8_T OFFSET_OMCI_TRAILER      = (OFFSET_OMCI_MSG_CONTENT +32);
constexpr UI8_T OFFSET_OMCI_TRAILER_RES  = (OFFSET_OMCI_TRAILER +0);
constexpr UI8_T OFFSET_OMCI_TRAILER_CPCS = (OFFSET_OMCI_TRAILER_RES +2);
constexpr UI8_T OFFSET_OMCI_TRAILER_CRC  = (OFFSET_OMCI_TRAILER_CPCS +2);

constexpr UI8_T OMCI_PKT_SIZE            = (OFFSET_OMCI_TRAILER_CRC +4);
constexpr UI8_T MAX_SET_ATTRS_OFFSET     = (OFFSET_OMCI_TRAILER +0);
constexpr UI8_T OFFSET_RESP_RESULT       = (OFFSET_OMCI_MSG_CONTENT +0);
constexpr UI8_T OFFSET_AttrsMask         = (OFFSET_OMCI_MSG_CONTENT +0);
constexpr UI8_T OMCI_MSG_CONTENT_SIZE    = 32;
constexpr UI8_T OMCI_GEM_HEADER_SIZE     = 5;

constexpr UI8_T OFFSET_SET_AttrsValue_START = (OFFSET_OMCI_ME_ID);

const std::map<UI8_T, std::string> g_action_t = 
{
    {0,"NO_SUPPORT",},
    {4,"CREATE",},
    {6,"DELETE"},
    {8,"SET",},
    {9,"GET"},
    {11,"GET_ALL_ALARMS"},
    {12,"GET_ALL_ALARMS_NEXT"},
    {13,"MIB_UPLOAD"},
    {14,"MIB_UPLOAD_NEXT"},
    {15,"MIB_RESET"},
    {16,"ALARM"},
    {17,"ATTRIBUTE_VALUE_CHANGE"},
    {18,"TEST"},
    {19,"START_SOFT_DOWNLOAD"},
    {20,"DOWNLOAD_SECTION"},
    {21,"END_SOFT_DOWNLOAD"},
    {22,"ACTIVATE_IMAGE"},
    {23,"COMMIT_IMAGE"},
    {24,"SYNCHRONIZE_TIME"},
    {25,"REBOOT"},
    {26,"GET_NEXT"},
    {27,"TEST_RESULT"},
    {28,"GET_CURRENT_DATA"},
    {29,"SET_ALU_NO_DATASYNC"},
};


static constexpr char PLAYBACK_CFG_NAME[]         = "PlayBack_Cfg";
static constexpr char PLAYBACK_OLT_CFG_NAME[]     = "PlayBack_OLT_Cfg";


class OMCI_Parser
{
    public:
        OMCI_Parser();

        static std::string get_omci_action_name(UI8_T action_ID);
        static UI16_T get_omci_action_id(std::string value);

        UI16_T omci_pkt_parser(UI8_T *pkt_p, UI8_T pkt_size);
        void   omci_play_back();

    private:
        std::string m_log_out_path;
        std::string m_log_in_path;
        Json::Value m_playback_cfg;
        ME_C   m_me;
        UI16_T m_playback_omci_num = {0};

        std::map<int, Json::Value> m_omci_playback;

        UI16_T get_omci_ui16(UI8_T *data);
        UI32_T get_omci_ui32(UI8_T *data);

        UI32_T get_Value_From_Pointer(UI8_T *ptr, UI8_T size);

        BOOL_T check_action_valid(UI16_T Class, UI16_T Action);
        BOOL_T check_me_class_valid(UI16_T Class);
        BOOL_T check_me_instance_valid(UI16_T Class ,UI16_T ME_ID);
        BOOL_T me_create_instance(UI16_T TransID ,UI16_T Class ,UI16_T ME_ID, UI8_T *pkt_p, UI8_T pkt_size);
        BOOL_T me_set_instance(UI16_T TransID ,UI16_T Class ,UI16_T ME_ID, UI8_T *pkt_p, UI8_T pkt_size);
        BOOL_T omci_parser_validaterxpkt (UI8_T * pkt_p);

        BOOL_T is_omci_log_enable();
        BOOL_T is_omci_play_enable();
        BOOL_T is_olt_play_enable();
        void   get_cfg();
        void   get_omci_playback_data();
};

#endif
