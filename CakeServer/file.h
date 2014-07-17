#ifndef CAKESERVER_FILE_H
#define CAKESERVER_FILE_H

namespace cakeserver {
    
    class File {
    public:
        File(const string& path, const string& ext);
        ~File();
        
        string path;
        char* content;
        string ext;
        size_t length;
    };
    
}

#endif