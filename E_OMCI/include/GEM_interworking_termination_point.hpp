
// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(GEM_INTERWORKING_TERMINATION_POINT_INCLUDE_HPP)
#define  GEM_INTERWORKING_TERMINATION_POINT_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>

class GEM_interworking_termination_point : public ME_S 
{
    public:
        GEM_interworking_termination_point();
        GEM_interworking_termination_point(int class_id,int instance_id, Json::Value me_s);

        ~GEM_interworking_termination_point();
        int m_2;
        char m_strin[256]={};
        void get_method();
};

#endif

