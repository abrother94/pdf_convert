#!/bin/bash

HEAD_TEMP()
{
local me_name="$1"
local UPPER=`echo $me_name | awk '{print toupper($0)}'`

echo "
// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
//  2.If want to add any new method , please also add another virtual 
//    function in ME_S class ,too.
// ------------------------------------------------------------------

#if !defined("$UPPER"_INCLUDE_HPP)
#define  "$UPPER"_INCLUDE_HPP

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>

class $me_name : public ME_S 
{
    public:
        $me_name();
        $me_name(int class_id,int instance_id, Json::Value me_s);

        ~$me_name();
        int m_2;
        char m_strin[256]={};
        void get_method();
};

#endif
"
}
