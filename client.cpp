#include "client.h"

#include <string>
#include <utility>

Client::Client() {}

void Client::run(const char* host, const char* port) {
    client_skt.setUpConnection(host, port);//ver si tengo q usar move
    getCommand();
}

void Client::getCommand() {
    std::string cmd;
    int received = -1;
    int sent = 0;
    do {
        std::cin >> cmd;
        sent = executeCommand(cmd);
        if (sent != 0) {
            received = receiveResponse();
            sent = 0;
        }
    }while (received != 0);
}

int Client::executeCommand(std::string cmd){
    if (cmd == "AYUDA") {
        return sendMessage('h');
    } else if (cmd == "RENDIRSE") {
        return sendMessage('s');
    } else {
        uint16_t num = 0;
        try {
            num = verifier.verifyCommand(std::move(cmd));
        } catch (std::exception& e) {
            std::cout << "Error: comando inválido. "
                         "Escriba AYUDA para obtener ayuda" << std::endl;
        }
        if (num != 0) return sendMessage(num);
    }
    return 0;
}

int Client::sendMessage(uint16_t num) {
    char to_send = 'n';
    client_skt.send(&to_send, 1);
    num = htons(num);
    return client_skt.send(&num, 2);
}

int Client::sendMessage(char to_send) {
    return client_skt.send(&to_send, 1);
}

int Client::receiveResponse(){
    uint32_t len = 0;
    int received = 0;
    received = client_skt.receive(&len, 4);
    len = ntohl(len);
    char* msg;//cambiar por vector?
    msg = new char[len + 2];
    client_skt.receive(msg, len);
    msg[len] = '\n';
    msg[len + 1] = '\0';
    std::cout << msg;
    if (!strncmp(msg, "Perdiste", 8) || !strncmp(msg, "Ganaste", 7))
        received = 0;
    delete [] msg;
    return received;
}

Client::~Client() {}
