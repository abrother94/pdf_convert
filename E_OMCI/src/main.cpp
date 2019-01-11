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
std::map<std::pair<int,int>, Json::Value> M_OMCI_G;

class Base 
{
    public:
        int m_1;
};

class B_1 : public Base
{
    public:
        int m_2;
};

class B_2 : public Base
{
    public:
        int m_3;
};


std::map<std::pair<int,int>, Base* > M_OMCI_P;


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

                if( Class == 256 )
                {
                    B_1 *A = new B_1();
                    A->m_2 = 2;
                    M_OMCI_P[std::make_pair(Class,Id)]=A;
                }
                else if( Class == 266 )
                {
                    B_2 *A = new B_2();
                    A->m_3 = 3;
                    M_OMCI_P[std::make_pair(Class,Id)]=A;
                }

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

    Base *BB = M_OMCI_P[std::make_pair(256, 0)]; 
    B_1 *BBC;
    BBC = static_cast<B_1*>(BB);
    printf("B 1 m_2=%d\r\n", BBC->m_2);

    BB = M_OMCI_P[std::make_pair(266,0)]; 
    B_2 *BBC2;
    BBC2 = static_cast<B_2*>(BB);
    printf("B 2 m_3=%d\r\n", BBC2->m_3);




    closedir(dir);
}

int main(int argc, char *argv[])
{
    get_omci_s();
    return 0;
}
