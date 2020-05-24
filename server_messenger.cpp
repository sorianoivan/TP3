#include "server_messenger.h"

Messenger::Messenger(Socket &&peer, int num) {
    this->peer = std::move(peer);
    this->secret_num = num;
    this->client_done = false;
    this->tries = 0;
}

Messenger::~Messenger() {}

bool Messenger::isDone(){
    return (client_done || tries >= 10);
}

void Messenger::run() {
    char cmd;
    //try catch?
    while (!isDone()) {
        cmd = receiveCommand();
        switch (cmd) {
            case 'h':
                sendHelp();
                break;
            case 's':
                client_done = true;
                sendLost();
                break;
            case 'n':
                receiveNum();
                break;
            default:
                break;
        }
    }
}

char Messenger::receiveCommand() {
    char cmd;
    peer.receive(&cmd, 1);//chequear exception
    return cmd;
}

void Messenger::receiveNum(){
    uint16_t test_num = 0;
    ++tries;
    peer.receive(&test_num, 2);
    test_num = ntohs(test_num);
    if (verifier.verifyNum(test_num) != 0) {
        sendInvalidNum();
    } else {
        compareNums(std::to_string(test_num));
    }
}

void Messenger::compareNums(std::string test_num) {
    char test_digit;
    char secret_digit;
    int bien = 0, regular = 0;
    for (int i = 0; i < 3; ++i) {
        test_digit = test_num[i];
        for (int j = 0; j < 3; ++j) {
            secret_digit = std::to_string(secret_num)[j];
            if (secret_digit == test_digit) {
                if (i == j) bien++;
                else
                    regular++;
            }
        }
    }
    if (tries < 10 || bien == 3)
        sendResponse(bien, regular);
    else
        sendLost();
}

void Messenger::sendResponse(unsigned short int bien, unsigned short int regular){
    std::stringstream response;
    uint32_t size = 0;
    if (bien != 0 && regular != 0) {
        response << bien << " bien, " << regular << " regular" << std::endl;
    } else if (bien == 0 && regular == 0){
        response << "3 mal" << std::endl;//PROTOCOLO
    } else if (bien == 0){
        response << regular << " regular" << std::endl;
    } else if (bien == 3){
        client_done = true;
        response << "Ganaste" << std::endl;
    } else {
        response << bien << " bien" << std::endl;
    }
    size = response.str().size() - 1;
    size = htonl(size);
    peer.send(&size, 4);
    size = htonl(size);
    peer.send(response.str().c_str(), size);
}

void Messenger::sendInvalidNum() {
    std::string invalid_num = "Número inválido. Debe ser de 3"
                              " cifras no repetidas";
    uint32_t size;
    size = invalid_num.size();
    size = htonl(size);
    peer.send(&size, 4);//mando el largo
    peer.send(invalid_num.c_str(), invalid_num.size());//mando el string
}

void Messenger::sendHelp(){
    std::string ayuda = "Comandos válidos:\n\tAYUDA: despliega la lista de"
                        " comandos válidos\n\tRENDIRSE: pierde el juego "
                        "automáticamente\n\tXXX: Número de 3 cifras a ser"
                        " enviado al servidor para adivinar el número secreto";
    uint32_t size;
    size = ayuda.size();
    size = htonl(size);
    peer.send(&size, 4);
    peer.send(ayuda.c_str(), ayuda.size());//chequear exception
}

void Messenger::sendLost(){
    std::string lost = "Perdiste";
    uint32_t size;
    size = lost.size();
    size = htonl(size);
    peer.send(&size, 4);
    peer.send(lost.c_str(), lost.size());
}
