#include <iostream>
#include <fstream>
#include <istream>
#include <test.hpp>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>


#include <json/json.hpp>
#include <json/json.h>

using namespace std;

static constexpr const char DEFAULT_SUBSCRIPTION_FILE_PATH[] = "./";

std::map<int, Json::Value> M_OMCI_S;

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
                int at =  omci_s["Class"].asInt();
                printf("insert at :%d\r\n", at);
                M_OMCI_S[at]=omci_s; 
                printf("vecotr size is %d\r\n", M_OMCI_S.size());
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
    return 0;
}
