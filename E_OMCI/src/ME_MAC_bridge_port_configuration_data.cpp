
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
#include <ME_MAC_bridge_port_configuration_data.hpp>

ME_MAC_bridge_port_configuration_data::ME_MAC_bridge_port_configuration_data()
{

}

ME_MAC_bridge_port_configuration_data::ME_MAC_bridge_port_configuration_data(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

ME_MAC_bridge_port_configuration_data::~ME_MAC_bridge_port_configuration_data()
{
    printf("~ME_MAC_bridge_port_configuration_data\r\n");
}

void ME_MAC_bridge_port_configuration_data::get_method()
{ 
    printf("ME_MAC_bridge_port_configuration_data get_method\r\n"); 
}



	
bool ME_MAC_bridge_port_configuration_data::attribute_1_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_2_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_3_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_4_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_5_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_6_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_7_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_8_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_9_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_10_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_11_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_12_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_MAC_bridge_port_configuration_data::attribute_13_method(Action in_Action, UI32_T *value, void *arg)
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

