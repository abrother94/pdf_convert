
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
#include <GEM_interworking_termination_point.hpp>

GEM_interworking_termination_point::GEM_interworking_termination_point()
{

}

GEM_interworking_termination_point::GEM_interworking_termination_point(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

GEM_interworking_termination_point::~GEM_interworking_termination_point()
{
    printf("~GEM_interworking_termination_point\r\n");
}

void GEM_interworking_termination_point::get_method()
{ 
    printf("GEM_interworking_termination_point get_method\r\n"); 
}



	
bool GEM_interworking_termination_point::attribute_1_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_2_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_3_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_4_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_5_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_6_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_7_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_8_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool GEM_interworking_termination_point::attribute_9_method(Action in_Action, UI32_T *value, void *arg)
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

