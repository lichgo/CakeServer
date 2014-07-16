#include "cs_types.h"
#include "server.h"

using namespace cakeserver;

int main(int argc, char* argv[]) {
    cout << "CakeServer start.\n";
    Server::getInstance().run();
//    ifstream ifs("/Users/lichgo/MicroCloud/Server/CakeServer/web/index.htm", std::ifstream::binary);
//    
//    if (ifs) {
//        ifs.seekg(0, ifs.end);
//        int length = (int)(ifs.tellg());
//        
//        char* content = new char[length];
//        
//        ifs.seekg(0, ifs.beg);
//        ifs.read(content, length);
//        
//        cout << content;
//        
//        ifs.close();
//    }
    cout << "CakeServer stop.\n";
}