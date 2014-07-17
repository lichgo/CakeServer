#ifndef CAKESERVER_SERVER_H
#define CAKESERVER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "file.H"

namespace cakeserver {
    
    class Server {
    public:
        virtual ~Server();
        static Server& getInstance();
        void run();
        
    private:
        Server();
        Server(const Server& src);
        Server& operator=(const Server& rhs);
        void response(int sockfd);
        void sendFile(const string& method, const string& filename, const string& ext, int sockfd);
        void clearCache();
        void parseRequest(char* req, string* method, string* path, string* ext);
    
        int sockfd;
        int err;
        int newfd;
        struct sockaddr_in address;
        
        unordered_map<string, File*> pathCache;
    };
    
}

#endif