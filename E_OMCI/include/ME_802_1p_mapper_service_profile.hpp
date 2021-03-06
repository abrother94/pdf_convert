/*
9.3.10 802.1p mapper service profile
This managed entity associates the priorities of 802.1P priority tagged frames with specific
connections. Instances of this managed entity are created and deleted by the OLT.
Relationships
At its root, an instance of this ME may be associated with zero or one instance of a PPTP UNI,
MAC bridge port configuration data, or any type of interworking termination point ME that carries
IEEE 802 traffic. Each of its eight branches is associated with zero or one GEM interworking
termination point.
Attributes
Managed entity id:            This attribute uniquely identifies each instance of this managed entity.
                              (R, Set-by-create) (mandatory) (2 bytes)
TP pointer:                   This attribute points to an instance of the associated termination point.
                              The termination point type is determined by the TP type attribute:
                              TP type          TP pointer points to?
                              0                Bridging mapping. Pointer should be set to 0xFFFF by
                                               OLT and ignored by ONT.
                              1                PPTP Ethernet UNI.
                              2                IP host config data.
                              3                Ethernet flow TP.
                              4                PPTP xDSL UNI.
                              5                PPTP 802.11 UNI.
                              6                PPTP MoCA UNI.
                              Not supported Bridging mapping if TP pointer value is 0xFFFF. TP
                                               pointer may also point to PPTP Ethernet UNI.
                              NOTE 1 ??When the TP type is xDSL, the two most significant bits may be
                              used to indicate a bearer channel.  (R, W, Set-by-create) (mandatory) (2 bytes)

                              Each of the following eight attributes points to the GEM interworking
                              termination point associated with the stated P-bit value. The null
                              pointer 0xFFFF specifies that frames with the associated priority are to be discarded.

ITP_PTR_FOR_PBIT_PRI 0:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 1:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 2:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 3:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 4:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 5:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 6:     (R, W, Set-by-create) (mandatory) (2 bytes)
ITP_PTR_FOR_PBIT_PRI 7:     (R, W, Set-by-create) (mandatory) (2 bytes)

Unmarked frame option:    This attribute specifies how the ONT should handle untagged Ethernet
                          frames received across the associated interface. Valid values include:
                          0   Convert from DSCP to 802.1p.
                          1   Tag frame to a certain value.
                          (R, W, Set-by-create) (mandatory) (1 byte)
DSCP to P-bit mapping:    This attribute is valid when the unmarked frame option attribute is set
                          to 0. The DSCP to P-bit attribute can be considered a bit string
                          sequence of 64 three-bit groupings. The 64 sequence entries represent
                          the possible values of the six-bit DSCP field. Each three-bit grouping
                          specifies the P-bit value to which the associated DSCP value should be
                          mapped. Once marked, the P-bit marked frame is then directed to the
                          GEM interworking termination point indicated by the interwork TP
                          pointer mappings. (R, W) (mandatory) (24 bytes)
                          NOTE 2 ??If certain bits in the DSCP field are to be ignored in the mapping
                          process, the attribute should be provisioned such that all possible values of
                          those bits produce the same P-bit mapping. This can be applied to the case
                          where the operator wishes to adopt the priority mechanism based on IP
                          precedence instead of full DSCP, which needs only the three MSBs of the
                          DSCP field.
Default P-bit marking:    This attribute is valid when the unmarked frame option attribute is set
                          to 1. The default P-bit marking attribute contains the default P-bit
                          priority setting to be applied. The P-bit marked frame is then directed
                          to the GEM interworking termination point indicated by the interwork
                          TP pointer mappings. (R, W, Set-by-create) (mandatory) (1 byte)
TP type:                      This attribute identifies the type of termination point associated with
                              the mapper.
                              0 Mapper used for bridging-mapping.
                              1 Mapper directly associated with a PPTP Ethernet UNI.
                              2 Mapper directly associated with an IP host service.
                              3 Mapper directly associated with an Ethernet flow termination point.
                              4 Mapper directly associated with a PPTP xDSL UNI.
                              5 Mapper directly associated with a PPTP 802.11 UNI.
                              6 Mapper directly associated with a PPTP MoCA UNI.
                              (R, W, Set-by-create) (optional) (1 byte)
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

#if !defined(ME_802_1P_MAPPER_SERVICE_PROFILE_INCLUDE_HPP)
#define  ME_802_1P_MAPPER_SERVICE_PROFILE_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_802_1p_mapper_service_profile : public ME_S 
{
    public:
        ME_802_1p_mapper_service_profile();
        ME_802_1p_mapper_service_profile(int class_id,int instance_id, Json::Value me_s);

        ~ME_802_1p_mapper_service_profile();
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


};
#endif

