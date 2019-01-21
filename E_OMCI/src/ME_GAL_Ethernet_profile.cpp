
// ------------------------------------------------------------------
//  1.Create by create_me_cpp.sh ME_NAME/XXX_XXX_XXX automatically
// ------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <istream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <typeinfo>
#include <ME_GAL_Ethernet_profile.hpp>

ME_GAL_Ethernet_profile::ME_GAL_Ethernet_profile()
{

}

ME_GAL_Ethernet_profile::ME_GAL_Ethernet_profile(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

ME_GAL_Ethernet_profile::~ME_GAL_Ethernet_profile()
{
    printf("~ME_GAL_Ethernet_profile\r\n");
}

void ME_GAL_Ethernet_profile::get_method()
{ 
    printf("ME_GAL_Ethernet_profile get_method\r\n"); 
}



	
bool ME_GAL_Ethernet_profile::attribute_1_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[0].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[0].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_GAL_Ethernet_profile::attribute_2_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[1].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[1].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}

