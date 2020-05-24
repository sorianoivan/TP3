#ifndef _SERVERMESSENGER_H
#define _SERVERMESSENGER_H

#include "common_socket.h"
#include "common_verifier.h"
#include "server_thread.h"
#include <string>
#include <sstream>
#include <atomic>
#include <utility>

class Messenger : public Thread {
private:
    Socket peer;
    Verifier verifier;
    int secret_num, tries;
    bool client_done;
    std::atomic<int>& winners;

public:
    Messenger(Socket&& peer, int num, std::atomic<int>& winners) :
                peer(std::move(peer)), secret_num(num),
                tries(0), client_done(false) , winners(winners){}
    void run() override;
    bool isDone() override;
    ~Messenger();

private:
    char receiveCommand();

    void sendHelp();

    void sendLost();

    void receiveNum();

    void sendInvalidNum();

    void compareNums(std::string test_num);

    void sendResponse(unsigned short int bien, unsigned short int regular);
};


#endif //_SERVERMESSENGER_H
