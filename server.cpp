#include "server.h"

#include <thread>
#include <algorithm>
#include <utility>

#define TERMINATING_CHAR 'q'

Server::Server() {
    done_accepting = false;
    total_clients = 0;
    clients_removed = 0;
    winners = 0;
}

void Server::run(const char* port, std::string numbers) {
    _getNumbers(numbers);

    bind_skt.setUpConnection(port);

    if (listen(bind_skt.getFd(), 10) == -1)
        throw SocketException(strerror(errno));

    get_char_thread = std::thread(&Server::_getTerminatingCmd, this);

    _acceptClients();

    _finish();
}

/* Pide a un FileReader que lea el archivo y llene la lista
 * de numeros secretos */
void Server::_getNumbers(std::string& numbers) {
    FileReader file_reader(std::move(numbers));
    file_reader(secret_nums);
}

/* Mientras el servidor siga escuchando se aceptaran clientes y
 * por cada uno que se acepta se lanza un hilo con un Messenger que se
 * comunica con dicho cliente */
void Server::_acceptClients() {
    unsigned int total_nums = secret_nums.size();
    while (!done_accepting) {
        Socket peer_skt;
        try {//Para agarrar la exception cuando cierre el socket
            peer_skt = bind_skt.accept();
        } catch (std::exception& e) {}
        if (peer_skt.getFd() != -1) {
            _addClient(peer_skt, total_nums);
        }
        _removeFinishedClients();
    }
}

void Server::_addClient(Socket& peer_skt, const unsigned int total_nums){
    unsigned int curr_num_index;
    curr_num_index = total_clients % total_nums;
    clients.push_back(new Messenger(std::move(peer_skt),
                                    secret_nums[curr_num_index],
                                    winners));

    clients[total_clients - clients_removed]->start();
    total_clients++;
}

/* Espera por entrada estandar al caracter que indica que el servidor no
 * aceptara mas clientes */
void Server::_getTerminatingCmd() {
    char cmd;
    do {
        std::cin >> cmd;
    }while (cmd != TERMINATING_CHAR);
    done_accepting = true;
    bind_skt.close();
}

/* Finaliza la ejecucion del server */
void Server::_finish(){
    _deleteClients();

    get_char_thread.join();

    _showResults();
}

/* Espera que se terminen las comunicaciones con los clientes que queden
 * y luego libera sus recursos */
void Server::_deleteClients(){
    for (auto & client : clients) {
        client->join();
        delete client;
    }
}

/* Esta funcion es utilizada por el metodo std::remove_if en
 * _removeFinishedClients para decidir que clientes debe
 * eliminar del vector. Antes de que sean eliminados se deben liberar
 * la memoria dinamica */
bool isClientDone(Thread* client) {
    if (client->isDone()){
        client->join();
        delete client;
        return true;
    }
    return false;
}

/* Remueve del vector a los clientes que ya hayan terminado su ejecucion */
void Server::_removeFinishedClients() {
    unsigned int clients_before, clients_after;

    clients_before = clients.size();
    clients.erase(std::remove_if(clients.begin(),
                                 clients.end(), isClientDone), clients.end());
    clients_after = clients.size();
    clients_removed += clients_before - clients_after;
}

/* Muestra la cantidad de ganadores y perdedores */
void Server::_showResults() const {
    std::cout << "Estadísticas:\n\tGanadores:  " << winners <<
              "\n\tPerdedores: " << total_clients - winners << std::endl;
}

Server::~Server() {}
