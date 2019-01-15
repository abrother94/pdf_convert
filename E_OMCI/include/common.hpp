#if !defined(COMMON_HPP_INCLUDED)
#define COMMON_HPP_INCLUDED

class ME_S
{
    public:

        Json::Value m_ME;
        ME_S():m_class_id(0),m_instance_id(0){return;};
        ME_S(int class_id,int instance_id):m_class_id(class_id),m_instance_id(instance_id){return;};
        virtual ~ME_S(){};
        virtual void get_method(){};
        virtual void set_method(){};
        virtual bool chk_action(std::string in_action){};

        int m_class_id;
        int m_instance_id;
};



#endif 
