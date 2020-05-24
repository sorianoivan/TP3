#include <iostream>

#include "client.h"

int main(int argc, char* argv[]) {
    if (argc != 3){
        std::cout << "Argumentos invalidos" << std::endl;
        return 0;
    }
    try{
        Client client;
        client.run(argv[1], argv[2]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 0;
    }
    return 0;//ver esto del retorno del cliente
}