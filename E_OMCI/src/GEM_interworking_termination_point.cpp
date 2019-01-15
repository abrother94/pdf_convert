
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


