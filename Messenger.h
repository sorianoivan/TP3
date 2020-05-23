#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include "Socket.h"
#include "Verifier.h"
#include <string>
#include <sstream>

class Messenger {// va a heredar de thread
private:
    Socket peer;
    Verifier verifier;
    int secret_num, tries;
    bool client_done, client_won;
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

    void sendResponse(int bien, int regular);

    bool isDone();
};


#endif //_SERVERMESSENGER_H
