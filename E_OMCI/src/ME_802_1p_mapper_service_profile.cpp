
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
#include <ME_802_1p_mapper_service_profile.hpp>

ME_802_1p_mapper_service_profile::ME_802_1p_mapper_service_profile()
{

}

ME_802_1p_mapper_service_profile::ME_802_1p_mapper_service_profile(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

ME_802_1p_mapper_service_profile::~ME_802_1p_mapper_service_profile()
{
    printf("~ME_802_1p_mapper_service_profile\r\n");
}

void ME_802_1p_mapper_service_profile::get_method()
{ 
    printf("ME_802_1p_mapper_service_profile get_method\r\n"); 
}



	
bool ME_802_1p_mapper_service_profile::attribute_1_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_802_1p_mapper_service_profile::attribute_2_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_802_1p_mapper_service_profile::attribute_3_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[2].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[2].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_4_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[3].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[3].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_5_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[4].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[4].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_6_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[5].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[5].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_7_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[6].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[6].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_8_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[7].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[7].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_9_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[8].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[8].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_10_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[9].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[9].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_11_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[10].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[10].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_12_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[11].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[11].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_13_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[12].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[12].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}


	
bool ME_802_1p_mapper_service_profile::attribute_14_method(Action in_Action, UI32_T *value, void *arg)
{
    switch(in_Action)
    {
        case MSG_TYPE_GET:
            {
                // Default action for value == 4bytes
		arg = (void *)&m_Attributes[13].Value;
                break;
            }
        case MSG_TYPE_SET:
            {
                // Default action for value == 4bytes
                m_Attributes[13].Value = *value;
                break;
            }
        default:
            {
                break;
            }
    }
    return true;
}

