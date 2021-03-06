#if !defined(COMMON_CLASS_HPP_INCLUDED)
#define COMMON_CLASS_HPP_INCLUDED

#include <common.hpp>

class Attribute_S
{
    public: 
        UI32_T Value;
        unsigned char * pValue;
};

class ME_S
{
    public:

        Json::Value m_j_me;
        ME_S():m_class_id(0),m_instance_id(0){return;};
        ME_S(UI32_T class_id, UI32_T instance_id, Json::Value me_s);

        virtual ~ME_S(){};
        virtual void get_method(){};
        virtual void set_method(){};

        UI32_T m_class_id;
        UI32_T m_instance_id;
        UI32_T m_actions_table=0;

        Attribute_S m_Attributes[17];
        Json::Value get_j_me(){return m_j_me;}; 
        void set_j_me(Json::Value i_m_me ){m_j_me = i_m_me;}; 

        virtual bool apply(std::string in_action){};

        virtual bool attribute_1_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_2_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_3_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_4_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_5_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_6_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_7_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_8_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_9_method( Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_10_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_11_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_12_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_13_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_14_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_15_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_16_method(Action in_Action, UI32_T *value, void *arg){};
        virtual bool attribute_17_method(Action in_Action, UI32_T *value, void *arg){};
};
#endif 
