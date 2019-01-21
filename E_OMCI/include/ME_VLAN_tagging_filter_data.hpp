/*
9.3.11 VLAN tagging filter data
This managed entity organizes data associated with VLAN tagging. Instances of this managed
entity are created and deleted by the OLT.
Relationships
An instance of this managed entity is associated with an instance of a MAC bridge port
configuration data managed entity. By definition, tag filtering occurs closer to the MAC bridge than
the tagging operation. Schematically, the ordering of the functions is:
ANI – Tag_operation – Tag_filtering – Bridging – Tag_filtering – Tag_operation – UNI
Attributes

Managed entity id:      This attribute uniquely identifies each instance of this managed entity.
                        Through an identical ID, this managed entity is implicitly linked to an
                        instance of the MAC bridge port configuration data ME.
                        (R, Set-by-create) (mandatory) (2 bytes)

VLAN filter list:       This attribute lists provisioned TCI values for the bridge port. A TCI
                        value (consisting of user priority, CFI and VID) is represented by
                        2 bytes. 12 VLAN entries are supported. The first N are valid, where N
                        is given by the number of entries attribute. (R, W, Set-by-create) (mandatory) (24 bytes)

Forward operation:      When a frame is received, it is processed according to the operation
                        specified by the forward operation table. (R, W, Set-by-create) (mandatory) (1 byte)
                        Forward     Type of received frame
                        operation   Tagged                                                    Untagged
                        0x00        Action (a)                                                Action (a)
                        0x01        Action (c)                                                Action (a)
                        0x02        Action (a)                                                Action (e)
                        0x03        Action (f) (VID investigation)                            Action (a)
                        0x04        Action (f) (VID investigation)                            Action (e)
                        0x05        Action (g) (VID investigation)                            Action (a)
                        0x06        Action (g) (VID investigation)                            Action (e)
                        0x07        Action (f) (user priority investigation)                  Action (a)
                        0x08        Action (f) (user priority investigation)                  Action (e)
                        0x09        Action (g) (user priority investigation)                  Action (a)
                        0x0A        Action (g) (user priority investigation)                  Action (e)
                        0x0B        Action (f) (TCI investigation)                            Action (a)
                        0x0C        Action (f) (TCI investigation)                            Action (e)
                        0x0D        Action (g) (TCI investigation)                            Action (a)
                        0x0E        Action (g) (TCI investigation)                            Action (e)
                        0x0F        Action (h) (VID investigation)                            Action (a)
                        0x10        Action (h) (VID investigation)                            Action (e)
                        0x11        Action (h) (user priority investigation)                  Action (a)
                        0x12        Action (h) (user priority investigation)                  Action (e)
                        0x13        Action (h) (TCI investigation)                            Action (a)
                        0x14        Action (h) (TCI investigation)                            Action (e)
                        0x15        Action (b) (Unconditional forwarding)                     Action (e)
                        This table and the actions are discussed in detail below.

Number of entries:      This attribute specifies the number of valid entries in the VLAN filter list. 
                        (R, W, Set-by-create) (mandatory) (1 byte)

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

#if !defined(ME_VLAN_TAGGING_FILTER_DATA_INCLUDE_HPP)
#define  ME_VLAN_TAGGING_FILTER_DATA_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_VLAN_tagging_filter_data : public ME_S 
{
    public:
        ME_VLAN_tagging_filter_data();
        ME_VLAN_tagging_filter_data(int class_id,int instance_id, Json::Value me_s);

        ~ME_VLAN_tagging_filter_data();
        int m_2;
        char m_strin[256]={};
        void get_method();


        bool  attribute_1_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_2_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_3_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_4_method(Action in_Action, unsigned *value, void *arg);


};
#endif

