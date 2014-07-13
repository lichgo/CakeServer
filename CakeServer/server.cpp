#include "cs_types.h"
#include "settings.h"
#include "server.h"

extern  "C" {
    int read(int, void*, int);
    int write(int, void*, int);
    int close(int);
}

using namespace cakeserver;

extern IntDict RESMSG;
extern StrDict MIMETYPE;

static struct Settings SETTINGS = {
    .bufLen = 1024,
    .port = 8000
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
        cout << "Responding to the client...\n";
        response(newfd);
        close(newfd);
    }
    
}

void Server::response(int sockfd) {
    
    char* buf = new char[SETTINGS.bufLen];

    read(sockfd, buf, SETTINGS.bufLen);
    cout << buf << '\n';
    
    if (!strncmp(buf, "GET", 3)) {
        char* file = buf + 4;
        char* space = strchr(file, ' ');
        *space = '\0';
        sendFile(file, sockfd);
    } else {
        cout << "Unsupport request.";
    }
    
}

void Server::sendFile(char* filename, int sockfd) {
    
    char* contents = "<html><body>Hello World</body></html>";
    
    if (!strcmp(filename, "/")) {
        write(sockfd, RESMSG[200], (int)strlen(RESMSG[200]));
        write(sockfd, contents, (int)strlen(contents));
    } else {
        write(sockfd, RESMSG[404], (int)strlen(RESMSG[404]));
    }
}
























