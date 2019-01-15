
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
#include <ONT_G.hpp>

ONT_G::ONT_G()
{

}

ONT_G::ONT_G(int class_id,int instance_id,  Json::Value me_s):ME_S(class_id, instance_id, me_s)
{

}

ONT_G::~ONT_G()
{
    printf("~ONT_G\r\n");
}

void ONT_G::get_method()
{ 
    printf("ONT_G get_method\r\n"); 
}


