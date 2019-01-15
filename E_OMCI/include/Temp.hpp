#!/bin/bash

HEAD_TMEP()
{
local me_name="$1"

echo "
#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>

class $me_name : public ME_S 
{
    public:
        $me_name();
        $me_name(int class_id,int instance_id);

        ~$me_name();
        int m_2;
        char m_strin[256]={};
        void get_method();
};
"
}
