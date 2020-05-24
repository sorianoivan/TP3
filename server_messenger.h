#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include "common_socket.h"
#include "common_verifier.h"
#include <string>
#include <sstream>

class Messenger {// va a heredar de thread
private:
    Socket peer;
    Verifier verifier;
    int secret_num, tries;
    bool client_done;
public:
    Messenger(Socket&& peer, int num);
    void run();//capaz conviene hacerla bool: true si gano false si perdio
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
