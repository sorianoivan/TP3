#include "Messenger.h"

Messenger::Messenger(Socket &&peer, int num) {
    this->peer = std::move(peer);
    this->secret_num = num;
    this->is_done = false;
}

Messenger::~Messenger() {}

void Messenger::run() {
    /* recibo char con tipo de comando */
    while (!is_done) {
        char cmd = receiveCommand();
        switch (cmd) {
            case 'h': /* ayuda */
                sendHelp();
                break;
            case 's':
                sendLost();
                is_done = true;
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
    char buff;
    peer.receive(&buff, 1);//chequear exception
    return buff;
}

void Messenger::receiveNum(){
    int test_num = 0;
    peer.receive(&test_num, 2);
    std::cout << test_num << std::endl;
}

void Messenger::sendHelp(){
    std::string ayuda = "ayuda";
    peer.send(ayuda.c_str(), 5);//chequear exception
}

void Messenger::sendLost(){
    std::string lost = "Perdiste";
    peer.send(lost.c_str(), 8);
}
