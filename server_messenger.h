#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include <string>
#include <sstream>
#include <atomic>
#include <utility>

#include "common_socket.h"
#include "common_verifier.h"
#include "server_thread.h"

class Messenger : public Thread {
private:
    Socket peer;
    Verifier verifier;
    int secret_num, tries;
    bool client_done;
    std::atomic<int>& winners;

public:
    /* Constructor */
    Messenger(Socket&& peer, int num, std::atomic<int>& winners) :
                peer(std::move(peer)), secret_num(num),
                tries(0), client_done(false) , winners(winners){}

    /* Recibe los comandos del cliente y envia la respuesta correspondiente */
    void run() override;
    /* Devuelve true si el cliente termino o intento mas de 10 veces.
     * Devuelve false en caso contrario */
    bool isDone() override;
    /* Destructor */
    ~Messenger();

private:
    char _receiveCommand();
    void _executeCommand(char cmd);
    void _receiveNum();
    void _compareNums(std::string test_num);
    void _sendResponse(const std::string &response);
    void _sendResponse(unsigned short int bien, unsigned short int regular);
    void _buildResponse(unsigned short bien, unsigned short regular,
            std::stringstream &response);
};

#endif //_SERVERMESSENGER_H
