/*
9.3.2    MAC bridge configuration data
This managed entity organizes status data associated with a MAC bridge. The ONT automatically
creates or deletes an instance of this managed entity upon the creation or deletion of a MAC bridge
service profile.
Relationships
This managed entity is associated with one instance of a MAC bridge service profile.
Attributes
Managed entity id:           This attribute uniquely identifies each instance of this managed entity.
                             Through an identical ID, this managed entity is implicitly linked to an
                             instance of the MAC bridge service profile. (R) (mandatory) (2 bytes)
Bridge MAC address:          This attribute indicates the MAC address used by the bridge. The ONT
                             sets this attribute to the value programmed into the ONT. (R)
                             (mandatory) (6 bytes)
Bridge priority:             This attribute reports the priority of the bridge. The ONT copies this
                             attribute from the priority attribute of the associated MAC bridge
                             service profile. The value of this attribute changes with updates to the
                             MAC bridge service profile priority attribute. (R) (mandatory)
                             (2 bytes)
Designated root:             This attribute identifies the bridge at the root of the spanning tree. It
                             comprises bridge priority (2 bytes) and MAC address (6 bytes). (R)
                             (mandatory) (8 bytes)
Root path cost:              This attribute reports the cost of the best path to the root as seen from
                             the bridge. Upon ME instantiation, the ONT sets this attribute to 0. (R)
                             (mandatory) (4 bytes)
Bridge port count:           This attribute records the number of ports linked to this bridge. (R)
                             (mandatory) (1 byte)
Root port num:               This attribute contains the port number that has the lowest cost from
                             the bridge to the root bridge. The value 0 means that this bridge is itself
                             the root. Upon ME instantiation, the ONT sets this attribute to 0. (R)
                             (mandatory) (2 bytes)
Hello time:                  This attribute is the hello time received from the designated root, the
                             interval (in 256ths of a second) between hello packets. Its range is
                             0x0100 to 0x0a00 (1..10 seconds) in accordance with [IEEE 802.1D].
                             (R) (optional) (2 bytes)
                              designated root (in 256ths of a second). Its range is 0x0400 to 0x1e00
                              (4..30 seconds) in accordance with [IEEE 802.1D]. (R) (optional)
                              (2 bytes)
Actions
Get, set
Notifications
None.
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ME_MAC_BRIDGE_CONFIGURATION_DATA_INCLUDE_HPP)
#define  ME_MAC_BRIDGE_CONFIGURATION_DATA_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_MAC_bridge_configuration_data : public ME_S 
{
    public:
        ME_MAC_bridge_configuration_data();
        ME_MAC_bridge_configuration_data(int class_id,int instance_id, Json::Value me_s);

        ~ME_MAC_bridge_configuration_data();
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


};
#endif

