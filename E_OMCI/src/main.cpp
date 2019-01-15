#include <iostream>
#include <fstream>
#include <istream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <typeinfo>

#include <json/json.hpp>
#include <json/json.h>
#include <common.hpp>
#include <all_me.hpp>

using namespace std;

static constexpr const char DEFAULT_SUBSCRIPTION_FILE_PATH[] = "./";


std::map<std::pair<int,int>, ME_S * > M_OMCI_P;
std::map<int, Json::Value> M_OMCI_S;
std::map<std::pair<int,int>, Json::Value> M_OMCI_G;


void release_all_me_obj()
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

void * get_me_obj(int class_id, int instance_id)
{
}

void create_me_obj(int class_id, int instance_id)
{
    ME_S *BB = NULL;
    BB = M_OMCI_P[std::make_pair(class_id, instance_id)];
    if (BB == NULL)
    {
        switch(class_id)
        {
            case 256:
                {
                    ONT_G *A = new ONT_G(class_id,instance_id);
                    M_OMCI_P[std::make_pair(class_id,instance_id)]=A;
                    break;
                }
            case 266:
                {
                    GEM_interworking_termination_point *A = new GEM_interworking_termination_point(class_id, instance_id);
                    M_OMCI_P[std::make_pair(class_id,instance_id)]=A;
                    break;
                }
            default:
                break;
        }
    }
    else
        printf("Already exist class_id [%d] instance_id[%d]!!\r\n", class_id, instance_id);
}

void get_omci_s()
{
    std::string ME_S_DIR="S_ME/";
    struct dirent *entry;

    DIR *dir = opendir(ME_S_DIR.c_str());

    if (dir == NULL) 
    {
        printf("no such path exist!!\r\n");
        return;
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

            printf("Open file ok\r\n");
            bool isJsonOK = (reader.parse(m_source_files, omci_s));

            if(isJsonOK)
            {
                printf("Get omci_s ok \r\n");
                printf("Class id:%d\r\n", omci_s["Class"].asInt());
                int Class =  omci_s["Class"].asInt();
                int Id =  omci_s["Id"].asInt();
                printf("insert at :%d\r\n", Class);
                M_OMCI_S[Class]=omci_s; 
                M_OMCI_G[std::make_pair(Class,Id)]=omci_s; 
                printf("s vecotr size is %d\r\n", M_OMCI_S.size());
                printf("g vecotr size is %d\r\n", M_OMCI_G.size());

                create_me_obj(Class, Id);

                printf("p vecotr size is %d\r\n", M_OMCI_P.size());
            }
            else
                printf("Get omci_s ng\r\n");
        }
        else
        {
            printf("Open file ng\r\n");
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    get_omci_s();

    int class_id = 256, instance_id = 0;
    {
        try 
        {
            switch(class_id)
            {
                case 256:
                    {
                        ME_S *BB =  M_OMCI_P[std::make_pair(class_id, instance_id)]; 
                        BB->get_method();
                        break;
                    }
                case 266:
                    {
                        ME_S *BB =  M_OMCI_P[std::make_pair(class_id, instance_id)]; 
                        BB->get_method();
                        break;
                    }
                default:
                    return NULL;
            }
        }
        catch(bad_cast) 
        {
            printf("ERROR-1 class_id[%d]\r\n", class_id);
            return NULL;
        }
    }
    release_all_me_obj();
    return 0;
}
