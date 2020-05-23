#include "Client.h"

Client::Client() {}

void Client::run(const char* host, const char* port) {
    client_skt.setUpConnection(host, port);//ver si tengo q usar move

    char buff[8];
    client_skt.receive(&buff, 8);
    std::cout << buff << std::endl;
}

/*void Client::getCommand() {
    std::string cmd;
    //int received = 0;
    //do {
        std::cin >> cmd;

        if (cmd == "AYUDA") {
            client_skt.send((const void *) 'h', 1);
            receiveResponse();
        } else if (cmd == "RENDIRSE") {
            client_skt.send((const void *) 's', 1);
            std::cout << "Rendirse" << std::endl;
            //receiveResponse();
        }
    //}while (received != 0);
}*/

int Client::receiveResponse(){
    //uint32_t len;
    std::string response;
    client_skt.receive(&response, 8);
    std::cout << response << std::endl;
    return 0;
}

Client::~Client() {}
