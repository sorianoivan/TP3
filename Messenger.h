#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include "Socket.h"
#include <string>

class Messenger {// va a heredar de thread
private:
    Socket peer;
    int secret_num;
    bool is_done;
public:
    Messenger(Socket&& peer, int num);
    void run();//capaz conviene hacerla bool: true si gano false si perdio
    ~Messenger();

private:
    char receiveCommand();

    void sendHelp();

    void sendLost();

    void receiveNum();
};


#endif //_SERVERMESSENGER_H
