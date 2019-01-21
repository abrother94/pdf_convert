/*
9.2.2    T-CONT
An instance of the traffic container managed entity T-CONT represents a logical connection group
associated with a PLOAM layer alloc-id. A T-CONT can accommodate GEM packets in priority
queues or traffic schedulers that exist in the GEM layer.
The ONT autonomously creates instances of this ME. The OLT can discover the number of
T-CONT instances via the ANI-G ME. When the ONT's MIB is reset or created for the first time,
all supported T-CONTs are created. The OLT provisions allocation-IDs to the ONT via the
PLOAM channel. The OLT must then set the alloc-id attributes in the T-CONTs that it wants to
activate for user traffic, to create the appropriate association between the allocation ID set in the
PLOAM channel and the T-CONT in the OMCI. Once that association is created, the mode
indicator attribute assumes the mode specified in the PLOAM channel. Note that there should be a
one-to-one relationship between allocation IDs and T-CONT MEs, and the connection of multiple
T-CONTs to a single allocation ID is undefined.
Note that the first allocation ID that is granted via the PLOAM channel is defined to be the default
alloc-id, and this alloc-id is the one that is used to carry the OMCC. The default alloc-id can also be
used to carry user traffic, and hence can be set into one of the T-CONT MEs. However, this OMCI
relationship only pertains to the user traffic, and the OMCC relationship is unaffected. It can also be
true that the OMCC is not contained in any T-CONT ME construct; rather, that the OMCC remains
outside of the OMCI, and the OMCI is not used to manage the OMCC in any way. The handling of
the multiplexing of OMCC and user data is discussed in clause 11.3.3.
Relationships
One or more instances of this managed entity are associated with an instance of a circuit pack that
supports a PON IF function, or the ONT-G itself.

Managed entity id:      This attribute uniquely identifies each instance of this managed entity. This
                        two-byte number indicates the physical capability that realizes the T-CONT.
                        It may be represented as 0xSSBB, where SS indicates the slot id that
                        contains this T-CONT (0 for the ONT as a whole), and BB is the T-CONT
                        id, numbered by the ONT itself. T-CONTs are numbered in ascending
                        order, with range 0..255 in each slot. (R) (mandatory) (2 bytes)

Alloc-id:     This attribute links the T-CONT with the alloc-id assigned by the OLT in
              the assign_allocID PLOAM message. Legal values range from 0 to 0x0FFF,
              with some values having special meaning as defined in [ITU-T G.984.3].
              Prior to setting of this attribute assignment by the OLT (via the OMCI channel).
              This attribute has default value 0x00FF.(R, W) (mandatory) (2 bytes)

Mode indicator:     This attribute indicates whether the T-CONT operates in ATM mode (0) or
                    GEM mode (1), as set via the PLOAM channel. ATM mode is deprecated;
                    this attribute should always have the value 1.  (R) (mandatory) (1 byte)

Policy:             This attribute indicates the T-CONT's traffic scheduling policy. Valid values:
                    0         Null.
                    1         HOL – Head of line queueing.
                    2         WRR – Weighted round robin.
                   (R) (mandatory) (1 byte)
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

#if !defined(ME_T_CONT_INCLUDE_HPP)
#define  ME_T_CONT_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_T_CONT : public ME_S 
{
    public:
        ME_T_CONT();
        ME_T_CONT(int class_id,int instance_id, Json::Value me_s);

        ~ME_T_CONT();
        int m_2;
        char m_strin[256]={};
        void get_method();


        bool  attribute_1_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_2_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_3_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_4_method(Action in_Action, unsigned *value, void *arg);


};
#endif

