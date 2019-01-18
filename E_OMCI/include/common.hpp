#if !defined(COMMON_HPP_INCLUDED)
#define COMMON_HPP_INCLUDED

#include <json/json.hpp>
#include <json/json.h>

#define SWITCHCASE(cid, ins_id, me_name, me_s) \
     case cid :\
     {\
         me_name *A = new me_name(cid, ins_id, me_s);\
         printf("CID[%d]\r\n", cid);\
         M_OMCI_P[std::make_pair(cid,ins_id)]=A;\
         break;\
     }

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


#endif 
