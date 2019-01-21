/*
9.3.28 Multicast subscriber config info
This managed entity organizes data associated with multicast management at subscriber ports of
802.1 bridges, including 802.1p mappers when the provisioning model is mapper-based rather than
bridge-based. Instances of this managed entity are created and deleted by the OLT. Because of
backward compatibility considerations, a subscriber port without an associated multicast subscriber
config info ME would be expected to support unrestricted multicast access; this ME may therefore
be viewed as restrictive, rather than permissive.
Relationships
An instance of this managed entity is associated with one instance of the MAC bridge port
configuration data or the 802.1p mapper service profile.
Attributes
Managed entity id:            This attribute uniquely identifies each instance of this managed entity.
                              Through an identical ID, this managed entity is implicitly linked to an
                              instance of the MAC bridge port configuration data or 802.1p mapper
                              ME. (R, Set-by-create) (mandatory) (2 bytes)

ME type:                      This attribute indicates the type of the ME implicitly linked by the
                              managed entity id attribute.
                              0     MAC bridge port config data.
                              1     802.1p mapper service profile.
                              (R, W, Set-by-create) (mandatory) (1 byte)

Multicast operations          This attribute points to an instance of the multicast operations profile.
profile pointer:              (R, W, Set-by-create) (mandatory) (2 bytes)

Max simultaneous groups:      This attribute specifies the maximum number of dynamic multicast
                              groups that may be replicated to the client port at any one time. The
                              default value 0 specifies that no administrative limit is to be imposed.
                              (R, W, Set-by-create) (optional) (2 bytes)

Max multicast bandwidth:      This attribute specifies the maximum imputed dynamic bandwidth, in
                              bytes per second, that may be delivered to the client port at any one
                              time. The default value 0 specifies that no administrative limit is to be
                              imposed. (R, W, Set-by-create) (optional) (4 bytes)

Bandwidth enforcement:        The default value of this Boolean attribute is false, and specifies that
                              attempts to exceed the max multicast bandwidth be counted but
                              honoured. The value true specifies that such attempts be counted and
                              denied. The imputed bandwidth value is taken from the dynamic access
                              control list table, both for a new join request and for pre-existing
                              groups. (R, W, Set-by-create) (optional) (1 byte)
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

#if !defined(ME_MULTICAST_SUBSCRIBER_CONFIG_INFO_INCLUDE_HPP)
#define  ME_MULTICAST_SUBSCRIBER_CONFIG_INFO_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_Multicast_subscriber_config_info : public ME_S 
{
    public:
        ME_Multicast_subscriber_config_info();
        ME_Multicast_subscriber_config_info(int class_id,int instance_id, Json::Value me_s);

        ~ME_Multicast_subscriber_config_info();
        int m_2;
        char m_strin[256]={};
        void get_method();


        bool  attribute_1_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_2_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_3_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_4_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_5_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_6_method(Action in_Action, unsigned *value, void *arg);


};
#endif

