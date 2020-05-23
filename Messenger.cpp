#include "Messenger.h"

Messenger::Messenger(Socket &&peer, int num) {
    this->peer = std::move(peer);
    this->secret_num = num;
    this->client_done = false;
    this->client_won = false;//ver si puedo simplificar esto
    this->tries = 0;
}

Messenger::~Messenger() {}

bool Messenger::isDone(){
    return (client_done || tries >= 10);
}

void Messenger::run() {
    /* recibo char con tipo de comando */
    std::string lost = "Perdiste";
    peer.send(lost.c_str(), lost.size());
    while (!isDone()) {
        char cmd = receiveCommand();
        switch (cmd) {
            case 'h': /* ayuda */
                sendHelp();
                break;
            case 's':
                //sendLost();
                client_done = true;
                break;
            case 'n':
                receiveNum();
                ++tries;
                break;
            default:
                break;
        }
    }
    if (!client_won) sendLost();
}

char Messenger::receiveCommand() {
    char buff;
    peer.receive(&buff, 1);//chequear exception
    return buff;
}

void Messenger::receiveNum(){
    int test_num = 0;
    peer.receive(&test_num, 2);
    if (verifier.verifyNum(test_num) != 0) sendInvalidNum();
    compareNums(std::to_string(test_num));
}

void Messenger::compareNums(std::string test_num) {
    char c;
    char v;
    int bien = 0, regular = 0;
    for (int i = 0; i < 3; ++i) {
        c = test_num.at(i);
        for (int j = 0; j < 3; ++j) {
            v = std::to_string(secret_num)[j];
            if (v == c) {
                if (i == j) bien++;
                else
                    regular++;
            }
        }
    }
    sendResponse(bien, regular);
}

void Messenger::sendResponse(int bien, int regular){
    std::stringstream response;
    if (bien != 0 && regular != 0) {
        response << bien << " bien, " << regular << " regular" << std::endl;
        peer.send(response.str().c_str(), response.str().size());
    } else if (bien == 0 && regular == 0){
        response << "3 mal" << std::endl;
        peer.send(response.str().c_str(), response.str().size());       //PROTOCOLO
    } else if (bien == 0){
        response << regular << " regular" << std::endl;
        peer.send(response.str().c_str(), response.str().size());
    } else if (bien == 3){
        response << "Ganaste" << std::endl;
        peer.send(response.str().c_str(), response.str().size());
        client_done = true;
        client_won = true;
    } else {
        response << bien << " bien" << std::endl;
        peer.send(response.str().c_str(), response.str().size());
    }
}

void Messenger::sendInvalidNum() {
    std::string invalid_num = "Número inválido. Debe ser de 3 cifras no repetidas";
    peer.send(invalid_num.c_str(), invalid_num.size());
}

void Messenger::sendHelp(){
    std::string ayuda = "Comandos válidos:\n\tAYUDA: despliega la lista de comandos válidos\n\tRENDIRSE: pierde el juego "
                        "automáticamente\n\tXXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    peer.send(ayuda.c_str(), ayuda.size());//chequear exception
}

void Messenger::sendLost(){
    std::string lost = "Perdiste";
    peer.send(lost.c_str(), lost.size());
}
