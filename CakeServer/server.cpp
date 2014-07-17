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
    .port = 8080
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
    
        string method;
        string path;
        string ext;
        parseRequest(buf, &method, &path, &ext);
        
        sendFile(method, path, ext, newfd);
        
        delete [] buf;
        close(newfd);
    }
    
}

void Server::sendFile(const string& method, const string& path, const string& ext, int sockfd) {
    
    File* file;
    
    unordered_map<string, File*>::iterator ptr = pathCache.find(path);
    if (ptr == pathCache.end()) {
        file = new File(path, ext);
        
        if (file->length) {
            pathCache[path] = file;
        } else {
            delete file;
            write(sockfd, Utils::strToCharArr(RESMSG[404]), (unsigned int)(RESMSG[404].length()));
            return;
        }
    } else {
        file = pathCache[path];
    }
    
    string header = "HTTP/1.1 200 " + STATUSCODE[200] + "\r\nContent-type, " + MIMETYPE[ext] + "\r\n\r\n";
    write(sockfd, Utils::strToCharArr(header), (unsigned int)(header.length()));
    write(sockfd, file->content, (unsigned int)file->length);
    
}

void Server::clearCache() {
    pathCache.clear();
}

void Server::parseRequest(char* req, string* method, string* path, string* ext) {
    char* space_1st_occr = strstr(req, " ");
    char* space_2nd_occr = strstr(space_1st_occr + 1, " ");
    (*method).append(req, space_1st_occr - req);
    (*path).append(space_1st_occr + 1, space_2nd_occr - (space_1st_occr + 1));
    size_t hit = (*path).find_last_of('.');
    if (hit != string::npos) (*ext) = (*path).substr(hit + 1);
}
























