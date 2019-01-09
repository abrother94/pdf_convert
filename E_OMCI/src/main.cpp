#include<iostream>
#include <test.hpp>
#include <json/json.hpp>
#include <json/json.h>

using namespace std;

static constexpr const char DEFAULT_SUBSCRIPTION_FILE_PATH[] = "./";

int main(int argc, char *argv[])
{
    std::string m_config_file_path = "266_GEM_interworking_termination_point";

    json::Value S_OMCI(json::Value::Type::OBJECT);
//    Json::Reader reader;

    std::cout << "Hello World!" << std::endl;
    return 0;
}
