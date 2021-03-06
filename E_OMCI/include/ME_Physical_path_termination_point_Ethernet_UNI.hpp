/*
9.5.1   Physical path termination point Ethernet UNI
This managed entity represents the point at an Ethernet UNI where the physical path terminates and
Ethernet physical level functions are performed.
The ONT automatically creates an instance of this managed entity per port:
•       When the ONT has Ethernet ports built into its factory configuration.
•       When a cardholder is provisioned to expect a circuit pack of Ethernet type.
•       When a cardholder provisioned for plug-and-play is equipped with a circuit pack of
        Ethernet type. Note that the installation of a plug-and-play card may indicate the presence
        of Ethernet ports via equipment ID as well as its type, and indeed may cause the ONT to
        instantiate a port mapping package that specifies Ethernet ports.
The ONT automatically deletes instances of this managed entity when a cardholder is neither
provisioned to expect an Ethernet circuit pack, nor is it equipped with an Ethernet circuit pack.
Relationships
An instance of this managed entity is associated with each instance of a preprovisioned or real
Ethernet port.
Attributes

Managed entity id:      This attribute uniquely identifies each instance of this managed entity.
                        This two-byte number indicates the physical position of the UNI. The
                        first byte is the slot id (defined in clause 9.1.5). The second byte is the
                        port ID, with range 1..255. (R) (mandatory) (2 bytes)

Expected type:          This attribute supports pre-provisioning. It is coded as follows:
                        0            Autosense.
                        1 to 254     One of the values from Table 9.1.5-1 that is compatible with an Ethernet circuit pack.
                        Upon ME instantiation, the ONT sets this attribute to 0. (R, W) (mandatory) (1 byte)

Sensed type:            When a circuit pack is present, this attribute represents its type as one of
                        the values from Table 9.1.5-1. If the value of expected type is not 0, then
                        the value of sensed type should be the same as the value of expected
                        type. Upon ME instantiation, the ONT sets this attribute to 0. See also
                        the note in the notifications below.
                        (R) (mandatory) (1 byte)

Auto detection          This attribute sets the Ethernet port configuration:
configuration:
                        Codepoint               Rate                     Duplex
                        0x00                  Auto                      Auto
                        0x01                 10 only              Full duplex only
                        0x02                100 only              Full duplex only
                        0x03               1000 only              Full duplex only
                        0x04                  Auto                Full duplex only
                        0x10                 10 only                    Auto
                        0x11                10 only               Half duplex only
                        0x12                100 only              Half duplex only
                        0x13               1000 only              Half duplex only
                        0x14                  Auto                Half duplex only
                        0x20               1000 only                    Auto
                        0x30                100 only                    Auto
                         Upon ME instantiation, the ONT sets this attribute to 0. (R, W) (mandatory) (1 byte)

Ethernet loopback       This attribute sets the Ethernet loopback configuration:
configuration:          0           No loopback.
                        3           Loop 3, loopback of downstream traffic after PHY
                        transceiver. Loop 3 is depicted in Figure 9.5.1-5.
                        Note that normal bridge behaviour may defeat the loopback signal, unless broadcast MAC
                        addresses are used. Upon ME instantiation, the ONT sets this attribute to 0. (R, W) (mandatory) (1 byte)
                        Figure 9.5.1-1 – Ethernet loopback configuration

Administrative state:         This attribute locks (1) and unlocks (0) the functions performed by this
                      managed entity. When the administrative state is set to lock, all user
                      functions of this UNI are blocked, and alarms, TCAs and AVCs for this
                      managed entity and all dependent managed entities are no longer
                      generated. Selection of a default value for this attribute is outside the
                      scope of this Recommendation. (R, W) (mandatory) (1 byte)

Operational state:     This attribute indicates whether or not the managed entity is capable of
                       performing its function. Valid values are enabled (0) and disabled (1).
                       (R) (optional) (1 byte)

Configuration ind:     This attribute indicates the configuration status of the Ethernet UNI.
                       0x01     10BaseT full duplex.
                       0x02     100BaseT full duplex.
                       0x03     Gigabit Ethernet full duplex.
                       0x11     10BaseT half duplex.
                       0x12     100BaseT half duplex.
                       0x13     Gigabit Ethernet half duplex.
                       The value 0 indicates that the configuration status is unknown (e.g.,
                       Ethernet link is not established or the circuit pack is not yet installed).
                       Upon ME instantiation, the ONT sets this attribute to 0. (R) (mandatory) (1 byte)

Max frame size:       This attribute denotes the maximum frame size allowed across this
                      interface. Upon ME instantiation, the ONT sets the attribute to 1518.
                      (R, W) (mandatory) (2 bytes)

DTE or DCE ind:       This attribute specifies the Ethernet interface wiring:
                      0     DCE (default).
                      1    DTE.
                      (R, W) (mandatory) (1 byte)

Pause time:           This attribute allows the PPTP to ask the subscriber terminal to
                      temporarily suspend sending data. Units are in pause quanta (1 pause
                      quantum is 512 bit times of the particular implementation). Values:
                      0..0xFFFF. Upon ME instantiation, the ONT sets this attribute to 0.
                      (R, W) (optional) (2 bytes)

Bridged or IP ind:    This attribute specifies whether the Ethernet interface is bridged or
                      derived from an IP router function
                      0     Bridged.
                      1     IP router.
                      2 Depends on the parent circuit pack. 2 means that the circuit pack's
                      bridged or IP ind attribute is either 0 or 1.
                      Upon ME instantiation, the ONT sets this attribute to 2. (R, W) (optional) (1 byte)

ARC:                  See clause I.1.8. (R, W) (optional) (1 byte)

ARC interval:         See clause I.1.8. (R, W) (optional) (1 byte)

PPPoE filter:         This attribute controls filtering of PPPoE packets on this Ethernet port.
                      The value 0 allows packets of all types. The value 1 discards everything
                      but PPPoE packets. The default value is 0. (R, W) (optional) (1 byte)

Power control:        equipment over the Ethernet PPTP. The value 1 enables power over the
                      Ethernet port. The default value 0 disables power feed. (R, W) (optional) (1 byte)
Actions
Get, set
Notifications
 Attribute value change
  Number        Attribute value change                                   Description
        1     N/A
        2     Sensed type                    Sensed type of Ethernet interface. Valid values are 1 (10BaseT), 2
                                             (100BaseT) and 3 (Gigabit Ethernet) (Note).
      3..5    N/A
        6     Op state                       Operational state
     7..11    N/A
       12     ARC                            ARC timer expiration
    13..15    N/A
       16     Reserved
 NOTE – These values violate the rules of the AVC message, which require the changed value of the sensed
 type (in this case) attribute to be reported. Because of existing implementations, pre-existing documentation
 is retained; however, implementers should regard this attribute and its AVC with caution.
 Alarm
  Number                  Alarm                                          Description
        0     LAN-LOS                        No carrier at the Ethernet UNI
    1..207    Reserved
  208..223 Vendor-specific alarms            Not to be standardized
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ME_PHYSICAL_PATH_TERMINATION_POINT_ETHERNET_UNI_INCLUDE_HPP)
#define  ME_PHYSICAL_PATH_TERMINATION_POINT_ETHERNET_UNI_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_Physical_path_termination_point_Ethernet_UNI : public ME_S 
{
    public:
        ME_Physical_path_termination_point_Ethernet_UNI();
        ME_Physical_path_termination_point_Ethernet_UNI(int class_id,int instance_id, Json::Value me_s);

        ~ME_Physical_path_termination_point_Ethernet_UNI();
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


        bool  attribute_14_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_15_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_16_method(Action in_Action, unsigned *value, void *arg);


};
#endif

