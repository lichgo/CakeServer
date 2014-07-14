#include "utils.h"

using namespace cakeserver;

char* Utils::strToCharPtr(const string& str) {
    char* ptr;
    strcpy(ptr, str.c_str());
    return ptr;
}