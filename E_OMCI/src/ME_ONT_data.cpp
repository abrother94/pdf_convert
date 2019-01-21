
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
#include <ME_ONT_data.hpp>

ME_ONT_data::ME_ONT_data()
{

}

ME_ONT_data::ME_ONT_data(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

ME_ONT_data::~ME_ONT_data()
{
    printf("~ME_ONT_data\r\n");
}

void ME_ONT_data::get_method()
{ 
    printf("ME_ONT_data get_method\r\n"); 
}



	
bool ME_ONT_data::attribute_1_method(Action in_Action, UI32_T *value, void *arg)
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


	
bool ME_ONT_data::attribute_2_method(Action in_Action, UI32_T *value, void *arg)
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

