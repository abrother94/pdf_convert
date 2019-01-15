#if !defined(COMMON_HPP_INCLUDED)
#define COMMON_HPP_INCLUDED

#define SWITCHCASE(cid, ins_id, me_name, me_s) do { \
{\
case cid: \
     me_name *A = new me_name(cid, ins_id, me_s);\
     M_OMCI_P[std::make_pair(cid,ins_id)]=A;\
     break;\
}\
} while (0)



class ME_S
{
    public:

        Json::Value m_ME;
        ME_S():m_class_id(0),m_instance_id(0){return;};
        ME_S(int class_id,int instance_id, Json::Value me_s):m_class_id(class_id),m_instance_id(instance_id),m_ME(me_s){return;};
        virtual ~ME_S(){};
        virtual void get_method(){};
        virtual void set_method(){};
        virtual bool chk_action(std::string in_action){};

        int m_class_id;
        int m_instance_id;
};



#endif 
