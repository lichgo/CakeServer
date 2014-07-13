#ifndef CAKESERVER_SERVER_H
#define CAKESERVER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

namespace cakeserver {
    
    class Server {
    public:
        virtual ~Server();
        static Server& getInstance();
        
    private:
        Server();
        
        static Server instance;
        static int sockfd;
        static int err;
        static int newfd;
        static struct sockaddr_in address;
    };
    
}

#endif