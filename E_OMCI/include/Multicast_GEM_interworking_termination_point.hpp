/*
9.2.5     Multicast GEM interworking termination point
An instance of this managed entity represents a point in the ONT where a multicast service
interworks with the GEM layer. At this point, a multicast bit stream is reconstructed from GEM
packets.
Instances of this managed entity are created and deleted by the OLT.
Multicast interworking GEM modes of operation
The default multicast operation of the PON is where all the multicast content streams are placed in
one PON layer connection (GEM port). This connection is then specified in the first entry of the
multicast address table. This single entry also specifies an all-inclusive IP multicast address range
(e.g., 224.0.0.0 to 239.255.255.255). The ONT then filters the traffic based on either Ethernet MAC
addresses or IP addresses. The GEM port network CTP ME contains the GEM port-ID that supports
all multicast connections.
An optional multicast operation is where groups of one or more multicast content streams are
carried over individual PON layer connections, i.e., on separate GEM ports, but terminate on a
single multicast GEM interworking termination point. In this case, the OLT sets as many table
entries as desired for the multicast control system. The ONT can initially filter groups based on
PON layer address (GEM port). In a subsequent step, the ONT can also filter based on higher-layer
addresses. In this case, the OLT need create only one instance of the GEM port network CTP ME.
Though this GEM port network CTP ME cites only one GEM port-ID, the ONT should regard this
ME as the representative of all multicast GEM connections served by the multicast GEM
interworking TP. The traffic descriptors, priority queues, and performance management features for
all multicast connections are integrated into the single GEM port network CTP ME.
Several multicast GEM interworking termination points can exist, each linked to separate bridge
ports or mappers to serve different communities of interest in a complex ONU.
Discovery of multicast support
The OLT uses the multicast GEM IW TP entity as the means to discover the ONT's multicast
capability. This entity is mandatory if multicasting is supported by the ONT. If the OLT attempts to
create this entity on an ONT that does not support multicast, the create command fails; likewise
with attempts to create a multicast address table with more than a single entry or to create multiple
GEM interworking termination points.
and a number of its attributes are not meaningful in a multicast context. These attributes are set to 0
and not used, as indicated below.
Relationships
An instance of this managed entity exists for each occurrence of transformation of GEM packets
into a multicast data stream.
Attributes
Managed entity id:            This attribute uniquely identifies each instance of this managed entity.
                              The value 0xFFFF is reserved. (R, Set-by-create) (mandatory) (2 bytes)
                              GEM port network CTP This attribute points to an instance of the GEM port network CTP that
connectivity pointer:         is associated with this multicast GEM interworking termination point.
                              (R, W, Set-by-create) (mandatory) (2 bytes)
Interworking option:          This attribute identifies the type of non-GEM function that is being
                              interworked. The option can be:
                              0        This value is a "no-op" or "do not care". It should be used
                                       when the multicast GEM IW TP is associated with several
                                       functions of different types. It can optionally be used in all
                                       cases, since the necessary information is available elsewhere.
                                       The previous codepoints are retained for backward
                                       compatibility.
                              1        MAC bridge LAN.
                              3        IP router.
                              5        802.1p mapper.
                              (R, W, Set-by-create) (mandatory) (1 byte)
Service profile pointer:      This attribute is set to 0 and not used. For backward compatibility, it
                              may also be set to point to a MAC bridge service profile, IP router
                              service profile or 802.1P mapper service profile. (R, W, Set-by-create) (mandatory) (2 bytes)
Interworking termination      This attribute is set to 0 and not used. (R, W, Set-by-create) (mandatory) (2 bytes)
point pointer:                
PPTP counter:                 This attribute represents the number of instances of PPTP managed
                              entities associated with this instance of the multicast GEM
                              interworking termination point. This attribute conveys no information
                              that is not available elsewhere; it may be set to 0xFF and not used. (R) (optional) (1 byte)
Operational state:            This attribute indicates whether or not the managed entity is capable of
                              performing its function. Valid values are enabled (0) and disabled (1).
                              (R) (optional) (1 byte)
GAL profile pointer:          This attribute is set to 0 and not used. For backward compatibility, it
                              may also be set to point to a GAL Ethernet profile. (R, W, Set-by-create) (mandatory) (2 bytes)
GAL loopback                  This attribute is set to 0 and not used. (R, W, Set-by-create) (mandatory) (1 byte)

configuration:                                              Each entry contains:
                              •         GEM port-ID                           2 bytes
                              •         Secondary index                       2 bytes
                              •         IP multicast address range start      4 bytes
                              •         IP multicast address range stop       4 bytes
                              The first four bytes of each entry are treated as the index of the list.
                              The secondary index allows the table to contain more than a single
                              range for a given GEM port.
                              A set action to a particular value overwrites any existing entry with the
                              same first four bytes. If the last eight bytes of a set command are all
                              zero, that entry is deleted from the list, as the all-zero IP address is not
                              valid.
                              One OMCI set message can convey up to two table entries. However,
                              OMCI does not provide robust exception handling when more than one
                              entry is included in a set command, and multiple entries per set
                              operation are not recommended.
                              (R, W) (mandatory) (12N bytes, where N is the number of entries in the list)
Actions
Create, delete, get, get next, set
Notifications
Attribute value change
  Number      Attribute value change                                Description
    1..5    N/A
      6     Op state                      Operational state change
    7..9    N/A
   10..16   Reserved
Alarm
  Number              Alarm                                         Description
      0     GFSA                          GEM frame starvation alarm
   1..207   Reserved
  208..223  Vendor-specific alarms        Not to be standardized
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(MULTICAST_GEM_INTERWORKING_TERMINATION_POINT_INCLUDE_HPP)
#define  MULTICAST_GEM_INTERWORKING_TERMINATION_POINT_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class Multicast_GEM_interworking_termination_point : public ME_S 
{
    public:
        Multicast_GEM_interworking_termination_point();
        Multicast_GEM_interworking_termination_point(int class_id,int instance_id, Json::Value me_s);

        ~Multicast_GEM_interworking_termination_point();
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


};
#endif

