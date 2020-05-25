#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <atomic>

#include "common_exception.h"
#include "common_socket_exception.h"
#include "server_file_reader.h"
#include "common_socket.h"
#include "server_messenger.h"

class Server {
private:
    Socket bind_skt;
    std::vector<int> secret_nums;
    std::vector<Thread*> clients;
    std::atomic<bool> done_accepting;
    std::thread get_terminating_cmd_th;

    unsigned int total_clients;
    unsigned int clients_removed;
    std::atomic<int> winners;

public:
    /* Constructor */
    Server();
    /* Comienza la ejecucion del server */
    void run(const char* port, std::string numbers);
    /* Destructor */
    ~Server();

private:
    void _getTerminatingCmd();
    void _acceptClients();
    void _getNumbers(std::string &numbers);
    void _deleteClients();
    void _removeFinishedClients();
    void _showResults() const;
    void _finish();
};

#endif //_SERVER_H
