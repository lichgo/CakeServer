#include "cs_types.h"
#include "file.h"

using namespace cakeserver;

File::File(const string& path, const string& ext) : path(path), ext(ext), length(0) {
    
    ifstream ifs("/Users/lichgo/MicroCloud/Server/CakeServer/web" + path, std::ios::in | std::ios::binary);
    
    if (ifs) {
        ifs.seekg(0, ifs.end);
        length = (int)(ifs.tellg());
        
        content = new char[length];
        
        ifs.seekg(0, ifs.beg);
        ifs.read(content, length);
        
        ifs.close();
    }
}

File::~File() {
    delete [] content;
}