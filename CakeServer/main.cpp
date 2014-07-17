#include "cs_types.h"
#include "server.h"

using namespace cakeserver;

int main(int argc, char* argv[]) {
    cout << "CakeServer start.\n";
    Server::getInstance().run();
    cout << "CakeServer stop.\n";
}