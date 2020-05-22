#include <iostream>
#include "Server.h"

int main(int argc, char* argv[]) {
    if (argc != 3){
        std::cerr << "Argumentos invalidos" << std::endl;
        return 1;
    }
    try{
        Server server;
        server.run(argv[1], argv[2]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
    return 0;
}