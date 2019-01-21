/*
9.3.27 Multicast operations profile
This managed entity expresses multicast policy. A multi-dwelling unit ONU may have several such
policies, which are linked to subscribers as required. Some of the attributes configure IGMP
snooping and proxy parameters, in case the defaults do not suffice, as described in
[b-IETF RFC 2236], [b-IETF RFC 3376], [b-IETF RFC 3810] and [b-IETF RFC 2933]. Instances
of this managed entity are created and deleted by the OLT.
Relationships
An instance of this managed entity may be associated with zero or more instances of the multicast
subscriber config info ME.
Attributes

Managed entity id:           This attribute uniquely identifies each instance of this managed entity.
                             The values 0 and 0xffff are reserved. (R, Set-by-create) (mandatory) (2 bytes)

IGMP version:                This attribute specifies the version of IGMP to be supported. Support of
                             a given version implies compatible support of previous versions. If the
                             ONT cannot support the version requested, it should deny an attempt to
                             write or create the ME. The default value is 2. 
                             1     IGMP version 1 (deprecated).
                             2     IGMP version 2.
                             3     IGMP version 3.
                             Other values reserved.
                              transparent IGMP snooping only. The value 1 specifies snooping with
                              proxy reporting (SPR); the value 2 specifies IGMP proxy. The function
                              must be consistent with the capabilities specified by the other IGMP
                              configuration attributes. (R, W, Set-by-create) (mandatory) (1 byte)

Immediate leave:              This Boolean attribute enables the immediate leave function. The
                              default value false disables immediate leave; true enables immediate leave.(R, W, Set-by-create) (mandatory) (1 byte)

Upstream IGMP TCI:       Under control of the upstream IGMP tag control attribute, the upstream
                         IGMP TCI attribute defines a VLAN ID and P-bits to add to upstream
                         IGMP messages. (R, W, Set-by-create) (optional) (2 bytes)

Upstream IGMP tag             This attribute controls the upstream IGMP TCI attribute. (R, W, Set-by-create) (optional) (1 byte)
control:                      

                              Value Meaning
                              0             Pass upstream IGMP traffic transparently, neither adding,
                                            stripping nor modifying tags that may be present.
                              1             Add a VLAN tag (including P-bits) to upstream IGMP
                                            traffic. The VLAN is specified by the upstream IGMP TCI
                                            attribute.
                              2             Replace the entire TCI (VLAN ID plus P-bits) on upstream
                                            IGMP traffic. The new tag is specified by the upstream
                                            IGMP TCI attribute.
                              3             Replace only the VLAN ID on upstream IGMP traffic,
                                            retaining the original CFI and P-bits. The new VLAN ID is
                                            specified by the VLAN field of the upstream IGMP TCI
                                            attribute.
                              Others        Reserved.

Upstream IGMP rate:           This attribute limits the maximum rate of upstream IGMP traffic.
                              Traffic in excess of this limit is silently discarded. The attribute value is
                              specified in messages/second. The default value 0 imposes no rate limit
                              on this traffic. (R, W, Set-by-create) (optional) (4 bytes)

Dynamic access control        This attribute is a list that specifies one or more multicast group address
list table:                   ranges. The ONT is expected to silently discard IGMP join requests for
                              groups that are not listed in this table.
                              (R, W) (mandatory) (24N bytes)

Static access control list    This attribute is a list that specifies one or more multicast group address
table:                        ranges. Groups defined in this list are multicast on the associated
                              UNI(s) unconditionally, that is, without the need for an IGMP join. The
                              bandwidth of static multicast groups is not included in the current
                              multicast bandwidth measurement maintained by the multicast
                              subscriber monitor managed entity. If a join message is always
                              expected, this table may be empty. Table entries have the same format
                              as those in the dynamic access control list table. (R, W) (mandatory) (24N bytes)

Lost groups list table:       This attribute is a list of groups from the dynamic access control list
                              table for which there is an active join, but no downstream flow is
                              present, possibly because of source failure, but also possibly because of
                              misconfiguration somewhere upstream. After a join, the ONT should
                              wait a reasonable time for upstream processing before declaring a group
                              to be lost. Each entry is a vector of the following components:
                              (R) (optional) (10N bytes)

Robustness:                   This attribute allows tuning for possible packet loss in the network. The
                              default value 0 causes the ONT to follow the IETF recommendation to
                              copy the robustness value from query messages originating further
                              upstream. (R, W, Set-by-create) (optional) (1 byte)

Querier IP address:           This attribute specifies the IP address to be used by a proxy querier.
                              Although it is not a legitimate IP address, the default value 0.0.0.0 is
                              legal in this case (see [b-IETF RFC 4541]). (R, W, Set-by-create) (optional) (4 bytes)

Query interval:               This attribute specifies the interval between general queries in seconds.
                              The default is 125 seconds. (R, W, Set-by-create) (optional) (4 bytes)

Query max response time:      This attribute is the max response time added by the proxy into general
                              query messages directed to UNIs. It is expressed in tenths of seconds,
                              with a default of 100 (10 seconds). (R, W, Set-by-create) (optional) (4 bytes)

Last member query             This attribute specifies the max response time inserted into
interval:                     group-specific queries sent to UNIs in response to group leave
                              messages. It is also the repetition rate of [robustness] transmissions of
                              the query. It is specified in tenths of seconds, with a default of 10 (1 second).  (R, W) (optional) (4 bytes)
Actions
Create, delete, get, get next, set
Notifications
        Alarm
        Number             Alarm                                       Description
             0    Lost multicast group       Indicates that for one or more multicast groups, there is an
                                             active join, but no downstream flow is present. This alarm
                                             is equivalent to a non-zero number of entries in the lost
                                             groups list table attribute. When the alarm is active, the
                                             OLT may use the table to retrieve the details of the lost
                                             group(s).
          1..207 Reserved
        208..223 Vendor-specific alarms      Not to be standardized
*/

// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ME_MULTICAST_OPERATIONS_PROFILE_INCLUDE_HPP)
#define  ME_MULTICAST_OPERATIONS_PROFILE_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_Multicast_operations_profile : public ME_S 
{
    public:
        ME_Multicast_operations_profile();
        ME_Multicast_operations_profile(int class_id,int instance_id, Json::Value me_s);

        ~ME_Multicast_operations_profile();
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

