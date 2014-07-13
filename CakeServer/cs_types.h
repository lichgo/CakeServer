#ifndef CAKESERVER_CS_TYPES_H
#define CAKESERVER_CS_TYPES_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <unordered_map>

using std::runtime_error;
using std::cout;
using std::string;
using std::unordered_map;

typedef unordered_map<int, char*> ResponseMsg;

#endif