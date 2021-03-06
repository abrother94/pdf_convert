/*
9.3.1   MAC bridge service profile
This managed entity models a MAC bridge in its entirety; any number of ports may then be
associated with the bridge through pointers to the MAC bridge service profile managed entity.
Instances of this managed entity are created and deleted by the OLT.
Relationships
Bridge ports are modelled by MAC bridge port configuration data managed entities, any number of
which can point to a MAC bridge service profile. The real-time status of the bridge is available
from an implicitly linked MAC bridge configuration data ME.
Attributes

Managed entity id:          This attribute uniquely identifies each instance of this managed entity.
                            The first byte is the slot id (defined in clause 9.1.5). If the UNI is
                            integrated, this value is 0. The second byte is the bridge group id.
                            (R, Set-by-create) (mandatory) (2 bytes)

Spanning tree ind:          The Boolean value true specifies that the spanning tree algorithm is
                            enabled. The value false disables spanning tree. (R, W, Set-by-create) (mandatory) (1 byte)

Learning ind:               The Boolean value true specifies that bridge learning functions are
                            enabled. The value false disables bridge learning. (R, W, Set-by-create) (mandatory) (1 byte)

Port bridging ind:          The Boolean value true specifies that bridging between UNI ports is
                            enabled. The value false disables local bridging. (R, W, Set-by-create) (mandatory) (1 byte)

Priority:                   This attribute specifies the bridge priority in the range 0..65535. The
                            value of this attribute is copied to the bridge priority attribute of the
                            associated MAC bridge configuration data managed entity. (R, W, Set-by-create) (mandatory) (2 bytes)

Max age:                    This attribute specifies the maximum age (in 256ths of a second) of
                            received protocol information before its entry in the spanning tree
                            listing is discarded. The range is 0x0600 to 0x2800 (6..40 seconds) in
                            accordance with [IEEE 802.1D]. (R, W, Set-by-create) (mandatory) (2 bytes)

Hello time:                 This attribute specifies how often (in 256ths of a second) the bridge
                            advertises its presence via hello packets while as a root or attempting to
                            become a root. The range is 0x0100 to 0x0a00 (1..10 seconds) in
                            accordance with [IEEE 802.1D]. (R, W, Set-by-create) (mandatory) (2 bytes)

Forward delay:              This attribute specifies the forwarding delay (in 256ths of a second)
                            when the bridge acts as the root. The range is 0x0400 to 0x1e00 (4..30
                            seconds) in accordance with [IEEE 802.1D]. (R, W, Set-by-create) (mandatory) (2 bytes)

Unknown MAC address         The Boolean value true specifies that MAC frames with unknown
discard:                    destination addresses be discarded. The value false specifies that such
                            frames be forwarded to all allowed ports. (R, W, Set-by-create) (mandatory) (1 byte)

MAC learning depth:         To be learned by the bridge. The default value 0 specifies that there is
                            no administratively-imposed limit. (R, W, Set-by-create) (optional) (1 byte)

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

#if !defined(ME_MAC_BRIDGE_SERVICE_PROFILE_INCLUDE_HPP)
#define  ME_MAC_BRIDGE_SERVICE_PROFILE_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_MAC_bridge_service_profile : public ME_S 
{
    public:
        ME_MAC_bridge_service_profile();
        ME_MAC_bridge_service_profile(int class_id,int instance_id, Json::Value me_s);

        ~ME_MAC_bridge_service_profile();
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


};
#endif

