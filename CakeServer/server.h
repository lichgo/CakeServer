#ifndef CAKESERVER_SERVER_H
#define CAKESERVER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

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
        void sendFile(const string& filename, int sockfd);
        void clearCache();
        void parseRequest(char* req, string* method, string* path);
    
        int sockfd;
        int err;
        int newfd;
        struct sockaddr_in address;
        
        StrDict pathCache;
    };
    
}

#endif