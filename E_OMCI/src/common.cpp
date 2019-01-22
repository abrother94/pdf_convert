#include <common.hpp>

BOOL_T mkdirp(const char* path, mode_t mode) 
{
    char* p = const_cast<char*>(path);

    while (*p != '\0') {
        p++;

        while(*p != '\0' && *p != '/') p++;

        char v = *p;

        *p = '\0';

        if(mkdir(path, mode) == -1 && errno != EEXIST) 
        {
            *p = v;
            return false;
        }
        *p = v;
    }

    return true;
}
