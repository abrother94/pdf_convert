#include <iostream>
#include <fstream>
#include <istream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <typeinfo>
#include <all_me.hpp>
#include <me_c.hpp>

ME_C::ME_C()
{
    if(get_omci_s())
    {
        printf("get_omci_s OK!!\r\n");
    }
    else
    {
        printf("get_omci_s NG!!\r\n");
        printf("###### SUPPORTED ME FILE ERROR #######!!!!\r\n");
    }
}

ME_C::~ME_C()
{
    release_all_me_obj();
}

void ME_C::release_all_me_obj()
{
    std::map < std::pair<int,int>, ME_S *>::iterator it;
    for(auto it = M_OMCI_P.begin(); it != M_OMCI_P.end(); ++it) 
    {
        ME_S * pME_S = it->second;
        if(pME_S)
        {
            delete pME_S;
        }
    }
    M_OMCI_P.clear();
}

ME_S * ME_C::get_me_obj(int class_id, int instance_id)
{
    ME_S *pTmp = NULL;
    pTmp =  M_OMCI_P[std::make_pair(class_id, instance_id)]; 
    if(!pTmp)
        return NULL;
    else
        return pTmp; 
}

// ------------------------------------------------------------------
// 1. Add SWITCHCASE( XXX_CID, instance_id, XXX_ME_NAME) after you 
//    use create_me_cpp.sh to create a new ME. 
// ------------------------------------------------------------------

BOOL_T ME_C::create_me_obj(int class_id, int instance_id, Json::Value me_s)
{
    ME_S *pME = NULL;

    printf("create me object class id [%d]\r\n", class_id);

    pME = M_OMCI_P[std::make_pair(class_id, instance_id)];
    if (pME == NULL)
    {
        switch(class_id)
        {
            SWITCHCASE(266 , instance_id, GEM_interworking_termination_point, me_s);
            SWITCHCASE(256 , instance_id, ONT_G, me_s);
            SWITCHCASE(281 , instance_id, Multicast_GEM_interworking_termination_point, me_s);
            default:
                break;
        }
        return true;
    }
    else
    {
        printf("Already exist class_id [%d] instance_id[%d]!!\r\n", class_id, instance_id);
        return false;
    }
}


// ------------------------------------------------------------------
// 1. Collect supported ME info in S_ME/
// ------------------------------------------------------------------

BOOL_T ME_C::get_omci_s()
{
    std::string ME_S_DIR(ME_SEC_PATH);
    struct dirent *entry;

    DIR *dir = opendir(ME_S_DIR.c_str());

    if (dir == NULL) 
    {
        printf("no such path exist!!\r\n");
        return false;
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        std::string dot(".");
        std::string ddot("..");

        std::string tmp_me_name = entry->d_name;

        if((dot == tmp_me_name) || (ddot == tmp_me_name))
            continue;

        std::string tmp_me_cid = tmp_me_name.substr(0, tmp_me_name.find("_"));
        printf("me name[%s] me cid[%s]\r\n", tmp_me_name.c_str(), tmp_me_cid.c_str());

        std::string m_config_file_path = ME_S_DIR + tmp_me_name ;
        printf("new pathname[%s]\r\n", m_config_file_path.c_str());

        ifstream    m_source_files= {};

        m_source_files.open(m_config_file_path);

        if(m_source_files.good())
        {   
            Json::Value omci_s;
            Json::Reader reader;
            BOOL_T isJsonOK = (reader.parse(m_source_files, omci_s));

            if(isJsonOK)
            {
                printf("Get omci_s ok \r\n");
                printf("Class id:%d\r\n", omci_s["Class"].asInt());
                int Class =  omci_s["Class"].asInt();
                int Id =  omci_s["Id"].asInt();
                //printf("insert Class at :%d\r\n", Class);
                //printf("insert Id at :%d\r\n", Id);
                //M_OMCI_S[Class]=omci_s; 
                M_OMCI_G[std::make_pair(Class,Id)]=omci_s; 
                //printf("s vecotr size is %d\r\n", M_OMCI_S.size());
                printf("g vecotr size is %zu\r\n", M_OMCI_G.size());
                create_me_obj(Class, 10, omci_s);
                //printf("p vecotr size is %zu\r\n", M_OMCI_P.size());
            }
            else
            {
                printf("Get omci_s ng\r\n");
                return false;
            }
        }
        else
        {
            printf("Open file ng\r\n");
            return false;
        }
    }

    closedir(dir);
    return true;
}

