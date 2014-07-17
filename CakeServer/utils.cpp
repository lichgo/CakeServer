#include "utils.h"

using namespace cakeserver;

char* Utils::strToCharArr(const string& str) {
    char* ptr = new char[str.length() + 1];
    for (int i = 0; i < str.length(); i++)
        *(ptr + i) = str[i];
    *(ptr + str.length()) = '\0';
    return ptr;
}