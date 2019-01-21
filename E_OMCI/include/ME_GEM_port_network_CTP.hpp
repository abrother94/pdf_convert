/*
9.2.3    GEM port network CTP
This managed entity represents the termination of a GEM port on an ONT. This managed entity
aggregates connectivity functionality from the network view and alarms from the network element
view as well as artefacts from trails.
Instances of the GEM port network CTP managed entity are created and deleted by the OLT. An
instance of GEM port network CTP can be deleted only when no GEM interworking termination
point or GEM port PM history data is associated with it. It is the responsibility of the OLT to make
sure that the GEM port network CTP meets this condition.
When a GEM port network CTP is created, its encryption state is by default not encrypted. If the
OLT wishes to configure the GEM port to use encryption, then the appropriate PLOAM message
must be sent. This applies equally to new CTPs or to CTPs that are re-created after a MIB reset.
Relationships
An instance of the GEM port network CTP managed entity may be associated with an instance of
the T-CONT and GEM interworking termination point managed entities.
Attributes

Managed entity id:       This attribute uniquely identifies each instance of this managed entity. (R, Set-by-create) (mandatory) (2 bytes)

Port id value:           This attribute is the port id of the GEM port associated with this CTP. (R, W, Set-by-create) (mandatory) (2 bytes)

T-CONT pointer:          This attribute points to a T-CONT instance. (R, W, Set-by-create) (mandatory) (2 bytes)
                         NOTE – In previous versions of this Recommendation, this attribute was
                         described as pointing to a PON TC adaptor-G. However, the latter ME had no
                         purpose, de facto, and has been omitted from this version. The instance identifier
                         of the PON TC adaptor was always defined to be identical to that of its
                         corresponding T-CONT, so this documentation change has no practical effect on
                         pre-existing implementations.

Direction:               This attribute specifies whether the GEM port is used for UNI-to-ANI (1),
                         ANI-to-UNI (2), or bidirectional (3) connection. (R, W, Set-by-create) (mandatory) (1 byte)

                         Traffic management If the traffic management option attribute in the ONT-G ME is 0 (priority controlled), 
			 this pointer specifies the priority queue-G ME serving this

pointer for upstream:    GEM port network CTP. If the traffic management option attribute is 1
                         (rate controlled), this attribute redundantly points to the T-CONT serving
                         this GEM port network CTP. (R, W, Set-by-create) (mandatory) (2 bytes)

Traffic descriptor       This attribute points to the instance of the GEM traffic descriptor managed
profile pointer:         entity that contains the traffic parameters used for this GEM port network
                         CTP ME. This attribute is used when the traffic management option
                         attribute in the ONT-G ME is 1 (rate controlled). (R, W, Set-by-create) (optional) (2 bytes)

                         See also Appendix III.
UNI counter:             This attribute reports the number of instances of UNI-G managed entity
                         associated with this GEM port network CTP. (R) (optional) (1 byte)

Priority queue pointer     This attribute points to the instance of the priority queue-G used for this
for downstream:            GEM port network CTP in the downstream direction. (R, W, Set-by-create) (mandatory) (2 bytes)

Encryption state:        This attribute indicates the current state of the GEM port network CTP's
                         encryption. Legal values are defined to be the same as those of the security
                         mode attribute of the ONT2-G, with the exception that attribute value 0
                         indicates an unencrypted GEM port. (R) (optional) (1 byte)
Actions
Create, delete, get, set
Notifications
 Alarm
  Number                    Alarm                                        Description
     0..4     Reserved
      5       End-to-end loss of continuity      Loss of continuity can be detected when the GEM port
                                                 network CTP supports a GEM interworking termination
                                                 point (optional)
   6..207     Reserved
  208..223    Vendor-specific alarms             Not to be standardized
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ME_GEM_PORT_NETWORK_CTP_INCLUDE_HPP)
#define  ME_GEM_PORT_NETWORK_CTP_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_GEM_port_network_CTP : public ME_S 
{
    public:
        ME_GEM_port_network_CTP();
        ME_GEM_port_network_CTP(int class_id,int instance_id, Json::Value me_s);

        ~ME_GEM_port_network_CTP();
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

