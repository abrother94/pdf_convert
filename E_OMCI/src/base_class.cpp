#include <base_class.hpp>
#include <string>
#include <omci_parser.hpp>

ME_S::ME_S(UI32_T class_id,UI32_T instance_id, Json::Value me_s)
{
    m_class_id    = class_id;
    m_instance_id = instance_id;
    m_j_me          = me_s;

    std::string action= m_j_me["Supported_Action"].asString();

    printf("Action[%s]\r\n", action.c_str());

    if(action.find("create") != std::string::npos )
    {
        m_actions_table |= OMCI_Parser::get_omci_action_id("CREATE");
        printf("C\r\n");
    }
    if(action.find("delete")!= std::string::npos )
    {
        m_actions_table |= OMCI_Parser::get_omci_action_id("DELETE");
        printf("D\r\n");
    }
    if(action.find("get")!= std::string::npos )
    {
        m_actions_table |= OMCI_Parser::get_omci_action_id("GET");
        printf("G\r\n");
    }
    if(action.find("set")!= std::string::npos )
    {
        m_actions_table |= OMCI_Parser::get_omci_action_id("SET");
        printf("S\r\n");
    }
    if(action.find("reboot")!= std::string::npos )
    {
        m_actions_table |= OMCI_Parser::get_omci_action_id("REBOOT");
        printf("R\r\n");
    }

    printf("action table[0x%04X]\r\n", m_actions_table);

    return;
};
