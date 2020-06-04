#ifndef _SERVER_H
#define _SERVER_H

#include <vector>
#include <string>

#include "common_exception.h"
#include "common_socket_exception.h"
#include "server_file_reader.h"
#include "common_socket.h"
#include "server_messenger.h"

class Server {
private:
    Socket bind_skt;
    std::vector<unsigned int> secret_nums;
    std::vector<Thread*> clients;
    std::atomic<bool> done_accepting;
    std::thread get_char_thread;

    unsigned int total_clients;
    unsigned int clients_removed;
    std::atomic<unsigned int> winners;

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
    void _addClient(Socket &peer_skt, const unsigned int total_nums);
    void _getNumbers(std::string &numbers);
    void _deleteClients();
    void _removeFinishedClients();
    void _showResults() const;
    void _finish();
};

#endif //_SERVER_H
