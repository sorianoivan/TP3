#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include "common_socket.h"
#include "common_verifier.h"
#include "server_thread.h"
#include <string>
#include <sstream>

class Messenger : public Thread {
private:
    Socket peer;
    Verifier verifier;
    int secret_num, tries;
    bool client_done;
public:
    Messenger(Socket&& peer, int num);
    void run() override;
    ~Messenger();

private:
    char receiveCommand();

    void sendHelp();

    void sendLost();

    void receiveNum();

    void sendInvalidNum();

    void compareNums(std::string test_num);

    void sendResponse(unsigned short int bien, unsigned short int regular);

    bool isDone();
};


#endif //_SERVERMESSENGER_H
