/*
9.3.4   MAC bridge port configuration data
This managed entity models a port on a MAC bridge. Instances of this managed entity are created
and deleted by the OLT.
Relationships
An instance of this managed entity is linked to an instance of the MAC bridge service profile.
Additional bridge port control capabilities are provided by implicitly linked instances of some or all
of:
•       MAC bridge port filter table data.
•       MAC bridge port filter preassign table.
•       VLAN tagging filter data.
•       Extended VLAN tagging operation config data.
Real-time status of the bridge port is provided by implicitly linked instances of:
•       MAC bridge port designation data.
•       MAC bridge port bridge table data.
Attributes
Managed entity id:           This attribute uniquely identifies each instance of this managed entity.
                             (R, Set-by-create) (mandatory) (2 bytes)

Bridge id pointer:           This attribute points to an instance of the MAC bridge service profile.
                             (R, W, Set-by-create) (mandatory) (2 bytes)

Port num:                    This attribute is the bridge port number. It must be unique among all
                             ports associated with a particular MAC bridge service profile. (R, W, Set-by-create) (mandatory) (1 byte)

TP type:                     This attribute identifies the type of termination point associated with
                             this MAC bridge port. Valid values are:
                             1    Physical path termination point Ethernet UNI.
                             2 Interworking VCC termination point.
                             3    802.1p mapper service profile.
                             4    IP host config data.
                             5    GEM interworking termination point.
                             6    Multicast GEM interworking termination point.
                             7    Physical path termination point xDSL UNI part 1.
                             8    Physical path termination point VDSL UNI.
                             9    Ethernet flow termination point.
                             10 Physical path termination point 802.11 UNI.
                             (R, W, Set-by-create) (mandatory) (1 byte)

TP pointer:                  This attribute points to the termination point associated with this MAC
                             bridge port. The TP type attribute indicates the type of the termination
                             point; this attribute contains its instance identifier (ME ID).
                             NOTE – When the TP type is VDSL or xDSL, the two most significant bits
                             may be used to indicate a bearer channel.
                             (R, W, Set-by-create) (mandatory) (2 bytes)

Port priority:              This attribute denotes the priority of the port. The range is 0..255.
                            (R, W, Set-by-create) (optional) (2 bytes)

Port path cost:             This attribute specifies the contribution of the port to the path cost
                            toward the spanning tree root bridge. The range is 1..65535. (R, W, Set-by-create) (mandatory) (2 bytes)

Port spanning tree ind:     The Boolean value true enables STP LAN topology change detection at
                            this port. The value false disables topology change detection. (R, W, Set-by-create) (mandatory) (1 byte)

Encapsulation method:       This attribute is not used. If it is present, it should be set to 1. (R, W, Set-by-create) (optional) (1 byte)

LAN FCS ind:                This attribute indicates whether frame check sequence bytes are
                            forwarded (0) or discarded (1). It is not expected to be needed in
                            G-PON applications, but is retained for backward compatibility. The
                            setting applies in both directions of transmission, and applies
                            regardless of encapsulation method, but it is meaningful only for ports
                            on the ANI side of the MAC bridge. The default value of this attribute
                            is 0. (R, W, Set-by-create) (optional) (1 byte) 

Port MAC address:           If the termination point associated with this port has a MAC address,
                            this attribute specifies it. (R) (optional) (6 bytes)

Outbound TD pointer:        This attribute points to a GEM traffic descriptor that limits the traffic
                            rate leaving the MAC bridge. (R, W) (optional) (2 bytes)

Inbound TD pointer:         This attribute points to a GEM traffic descriptor that limits the traffic
                            rate entering the MAC bridge. (R, W) (optional) (2 bytes)

Actions
Create, delete, get, set
Notifications
None.
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ME_MAC_BRIDGE_PORT_CONFIGURATION_DATA_INCLUDE_HPP)
#define  ME_MAC_BRIDGE_PORT_CONFIGURATION_DATA_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_MAC_bridge_port_configuration_data : public ME_S 
{
    public:
        ME_MAC_bridge_port_configuration_data();
        ME_MAC_bridge_port_configuration_data(int class_id,int instance_id, Json::Value me_s);

        ~ME_MAC_bridge_port_configuration_data();
        int m_2;
        char m_strin[256]={};
        void get_method();


        bool  attribute_1_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_2_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_3_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_4_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_5_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_6_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_7_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_8_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_9_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_10_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_11_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_12_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_13_method(Action in_Action, unsigned *value, void *arg);


};
#endif

