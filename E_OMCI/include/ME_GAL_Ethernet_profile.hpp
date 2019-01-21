/*
9.2.7    GAL Ethernet profile
This managed entity organizes data that describes the GTC adaptation layer processing functions of
the ONT for Ethernet services. It is used with the GEM interworking termination point managed
entity.
Instances of this managed entity are created and deleted on request of the OLT.
Relationships
An instance of this managed entity may be associated with zero or more instances of the GEM
interworking termination point managed entity.
Attributes
Managed entity id:           This attribute uniquely identifies each instance of this managed entity.
                             (R, Set-by-create) (mandatory) (2 bytes)
                             Maximum GEM payload This attribute defines the maximum payload size generated in the
size:                        associated GEM interworking termination point managed entity.
                             (R, W, Set-by-create) (mandatory) (2 bytes)
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

#if !defined(ME_GAL_ETHERNET_PROFILE_INCLUDE_HPP)
#define  ME_GAL_ETHERNET_PROFILE_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <base_class.hpp>

class ME_GAL_Ethernet_profile : public ME_S 
{
    public:
        ME_GAL_Ethernet_profile();
        ME_GAL_Ethernet_profile(int class_id,int instance_id, Json::Value me_s);

        ~ME_GAL_Ethernet_profile();
        int m_2;
        char m_strin[256]={};
        void get_method();


        bool  attribute_1_method(Action in_Action, unsigned *value, void *arg);


        bool  attribute_2_method(Action in_Action, unsigned *value, void *arg);


};
#endif

