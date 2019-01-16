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

enum Action 
{ 
    MSG_TYPE_GET    = 1, 
    MSG_TYPE_SET    = 2 
}; 

typedef unsigned int    UI32_T;
typedef unsigned short  UI16_T;
typedef unsigned char   UI8_T;
typedef unsigned char   BOOL_T;
typedef int             I32_T;
typedef short           I16_T;
typedef char            I8_T;


// ------------------------------------------------------------------
//  1. to save attribute value 
//     Value <= 4bytes 
//     pValue >= 4bytes // Need allocate memory and release by itself
// ------------------------------------------------------------------
class Attribute_S
{
    public: 
        UI32_T Value;
        unsigned char * pValue;
};

class ME_S
{
    public:

        Json::Value m_ME;
        ME_S():m_class_id(0),m_instance_id(0){return;};
        ME_S(int class_id,int instance_id, Json::Value me_s):m_class_id(class_id),m_instance_id(instance_id),m_ME(me_s){return;};
        virtual ~ME_S(){};
        virtual void get_method(){};
        virtual void set_method(){};

        int m_class_id;
        int m_instance_id;

        Attribute_S m_Attributes[17];

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
