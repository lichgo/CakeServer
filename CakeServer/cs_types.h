#ifndef CAKESERVER_CS_TYPES_H
#define CAKESERVER_CS_TYPES_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>

using std::runtime_error;
using std::cout;
using std::string;
using std::unordered_map;
using std::set;
using std::ifstream;
using std::pair;
using std::vector;

typedef unordered_map<int, string> IntDict;
typedef unordered_map<string, string> StrDict;

#endif