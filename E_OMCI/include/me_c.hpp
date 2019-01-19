#if !defined(ME_S_HPP_INCLUDED)
#define ME_S_HPP_INCLUDED

#include <common.hpp>
#include <base_class.hpp>
#include <json/json.hpp>
#include <json/json.h>

using namespace std;

static constexpr const char DEFAULT_SUBSCRIPTION_FILE_PATH[] = "./";
static constexpr const char ME_SEC_PATH[] = "S_ME/";

class ME_C
{
    public:

        std::map<std::pair<int,int>, ME_S * > M_OMCI_P;
        std::map<std::pair<int,int>, Json::Value> M_OMCI_G;

        ME_C();
        ~ME_C();
        ME_S * get_me_obj(int class_id, int instance_id);
        BOOL_T create_me_obj(int class_id, int instance_id, Json::Value me_s);
        BOOL_T check_action_valid(UI16_T Class, UI16_T Action);
        BOOL_T check_me_s_valid(UI16_T Class);

    private:
        BOOL_T get_omci_s();
        void release_all_me_obj();
};

#endif
