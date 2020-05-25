#ifndef _CLIENT_H
#define _CLIENT_H

#include <iostream>
#include <string>
#include <vector>

#include "common_socket.h"
#include "common_verifier.h"


class Client {
private:
    Socket client_skt;
    Verifier verifier;
public:
    /* Constructor */
    Client();
    /* Ejecuta el cliente */
    void run(const char* host, const char* port);
    /* Destructor */
    ~Client();

private:
    void _guessNumber();
    int _executeCommand(const std::string& cmd);
    int _sendMessage(const char to_send);
    int _sendMessage(uint16_t num);
    int _receiveResponse();
};

#endif //_CLIENT_H
