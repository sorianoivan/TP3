#ifndef _CLIENT_H
#define _CLIENT_H

#include <string>

#include "common_socket.h"
#include "common_verifier.h"
#include <iostream>

class Client {
private:
    Socket client_skt;
    Verifier verifier;
public:
    Client();
    void run(const char* host, const char* port);
    ~Client();

    void getCommand();

    int receiveResponse();

    int sendMessage(char to_send);
    int sendMessage(uint16_t num);

    /*int sendNum(uint16_t num);

    int sendHelpRequest();

    int giveUp();*/
    int executeCommand(std::string cmd);
};


#endif //_CLIENT_H
