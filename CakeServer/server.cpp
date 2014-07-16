#include "cs_types.h"
#include "settings.h"
#include "server.h"
#include "utils.h"
#include "global.h"

extern  "C" {
    int read(int, void*, int);
    int write(int, void*, int);
    int close(int);
}

using namespace cakeserver;

static struct Settings SETTINGS = {
    .bufLen = 1024,
    .port = 8888
};

Server::Server() {
    
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

Server::~Server() {
    
}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

void Server::run() {

    cout << "Waiting for connection...\n";
    
    while (true) {
        newfd = accept(sockfd, NULL, NULL);
        
        char* buf = new char[SETTINGS.bufLen];
        read(newfd, buf, (unsigned int)SETTINGS.bufLen);
        cout << buf << '\n';
    
        string method;
        string path;
        parseRequest(buf, &method, &path);
        cout << "METHOD: " << method << '\n';
        cout << "PATH: " << path << '\n';
        
        sendFile(path, newfd);
        
        delete [] buf;
        close(newfd);
    }
    
}

//void Server::response(int sockfd) {
//    
//    char* buf = new char[SETTINGS.bufLen];
//
//    read(sockfd, buf, (unsigned int)SETTINGS.bufLen);
//    cout << buf << '\n';
//    
//    string method, path;
//    parseRequest(buf, &method, &path);
//    cout << "Method: " << method << std::endl;
//    cout << "Path: " << path << std::endl;
//    
//    if (!strncmp(buf, "GET", 3)) {
//        char* file = buf + 4;
//        char* space = strchr(file, ' ');
//        *space = '\0';
//        sendFile(file, sockfd);
//    } else {
//        cout << "Unsupport request.";
//    }
//    
//}

void Server::sendFile(const string& filename, int sockfd) {
    
    char* content;
    int length;
    Utils::fileToCharArr(filename, &content, &length);
    
    if (content) {
        write(sockfd, Utils::strToCharArr(RESMSG[200]), (unsigned int)(RESMSG[200].length()));
        write(sockfd, content, length);
    } else {
        write(sockfd, Utils::strToCharArr(RESMSG[404]), (unsigned int)(RESMSG[404].length()));
    }
    
}

void Server::clearCache() {
    
}

void Server::parseRequest(char* req, string* method, string* path) {
    char* space_1st_occr = strstr(req, " ");
    char* space_2nd_occr = strstr(space_1st_occr + 1, " ");
    (*method).append(req, space_1st_occr - req);
    (*path).append(space_1st_occr + 1, space_2nd_occr - space_1st_occr);
}
























