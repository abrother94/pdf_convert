
// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined(ONT_G_INCLUDE_HPP)
#define  ONT_G_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>

class ONT_G : public ME_S 
{
    public:
        ONT_G();
        ONT_G(int class_id,int instance_id, Json::Value me_s);

        ~ONT_G();
        int m_2;
        char m_strin[256]={};
        void get_method();
};

#endif
