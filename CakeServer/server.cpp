#include "cs_types.h"
#include "settings.h"
#include "server.h"

using namespace cakeserver;

static struct Settings SETTINGS = {
    .bufLen = 1024,
    .port = 8000
};

Server::Server() {}

Server::~Server() {}

Server& Server::getInstance() {
    
    // Initialize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw new runtime_error("Failed to initialize socket.");
    }
    
    // Initialize address
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(SETTINGS.port);
    address.sin_addr.s_addr = INADDR_ANY;
    
    // Socket binding
    if (bind(sockfd, (struct sockaddr*)&address, sizeof(struct sockaddr_in))) {
        throw new runtime_error("Socket binding error.");
    }
    
    listen(sockfd, 128);
    
}