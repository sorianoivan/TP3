#ifndef _CLIENT_H
#define _CLIENT_H

#include "common_socket.h"
#include "common_verifier.h"

#include <string>

class Client {
private:
    Socket client_skt;
    Verifier verifier;
public:
    /* Constructor */
    Client();
    /* Comienza la ejecucion del cliente */
    void run(const char* host, const char* port);
    /* Destructor */
    ~Client();

private:
    void _guessNumber();
    int _executeCommand(const std::string& cmd);
    int _sendMessage(const char to_send);
    int _sendMessage(int16_t num);
    int _receiveResponse();
};

#endif //_CLIENT_H
