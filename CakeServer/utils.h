#ifndef CAKESERVER_UTILS_H
#define CAKESERVER_UTILS_H

#include "cs_types.h"

namespace cakeserver {
    
    class Utils {
    public:
        static char* strToCharArr(const string& str);
        static void fileToCharArr(const string& path, char** content, int* length);
    };
    
}

#endif