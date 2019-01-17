#!/bin/bash

HEAD_TOP()
{
    local me_name="$1"
    local att_num="$2"
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
#include <common_class.hpp>

class $me_name : public ME_S 
{
    public:
        $me_name();
        $me_name(int class_id,int instance_id, Json::Value me_s);

        ~$me_name();
        int m_2;
        char m_strin[256]={};
        void get_method();
"
}

HEAD_BOT()
{
    local me_name="$1"
    local att_num="$2"
    local UPPER=`echo $me_name | awk '{print toupper($0)}'`
echo "
};
#endif
"
}

HEAD_ATT()
{
    local me_name="$1"
    local att_num="$2"

    for(( n=1; n <= "$att_num" ;n++))
    do
echo "
        bool  attribute_"$n"_method(Action in_Action, unsigned *value, void *arg);
"
    done
}


HEAD_TEMP()
{
    local me_name="$1"
    local att_num="$2"
    local sec="$3"
    BN=`basename "$sec"`
    echo "/*"
    ME_INF=`cat ./ME_NAME/$BN`
    echo "$ME_INF"
    echo "*/"
    HEAD_TOP "$me_name" "$att_num"
    HEAD_ATT "$me_name" "$att_num"
    HEAD_BOT "$me_name" "$att_num"
}
