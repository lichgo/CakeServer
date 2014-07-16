#include "utils.h"

using namespace cakeserver;

char* Utils::strToCharArr(const string& str) {
    char* ptr = new char[str.length() + 1];
    for (int i = 0; i < str.length(); i++)
        *(ptr + i) = str[i];
    *(ptr + str.length()) = '\0';
    return ptr;
}

void Utils::fileToCharArr(const string& path, char** content, int* length) {
    
    ifstream ifs("/Users/lichgo/MicroCloud/Server/CakeServer/web" + path, ifs.out);
    
    if (ifs.fail() == 0) {
        ifs.seekg(0, ifs.end);
        *length = (int)(ifs.tellg());
        
        *content = new char[*length];
        
        ifs.seekg(0, ifs.beg);
        ifs.read(*content, *length);

        cout << "LENGTH: " << *length << ".\n";
        
        ifs.close();
    } else {
        *length = 5;
        char buf[] = "Hello";
        *content = buf;
    }
}