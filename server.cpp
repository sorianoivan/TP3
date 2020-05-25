#include "server.h"

#include <thread>
#include <algorithm>
#include <utility>

Server::Server() {
    done_accepting = false;
    total_clients = 0;
    clients_removed = 0;
    winners = 0;
}

bool isClientDone(Thread* client) {
    if (client->isDone()){
        client->join();
        delete client;
        return true;
    }
    return false;
}

void Server::run(const char* port, std::string numbers) {
    FileReader file_reader(std::move(numbers));
    file_reader.processFile(secret_nums);

    bind_skt.setUpConnection(port);
    if (listen(bind_skt.getFd(), 10) == -1)
        throw SocketException("Error listen");

    std::thread th(&Server::getChar, this);

    acceptClients();

    for (auto & client : clients) {
        client->join();
        delete client;
    }
    th.join();
    std::cout << "Estadísticas:\n\tGanadores:  " << winners <<
    "\n\tPerdedores: " << total_clients - winners << std::endl;
}

void Server::acceptClients() {
    unsigned int curr_num;
    int clients_before = 0;
    int clients_after = 0;
    while (!doneAccepting()) {
        Socket peer_skt;
        try {
            peer_skt = bind_skt.accept();
        } catch (std::exception& e) {}
        if (peer_skt.getFd() != -1) {
            curr_num = total_clients % secret_nums.size();
            clients.push_back(new Messenger(std::move(peer_skt),
                    secret_nums[curr_num], winners));
            clients[total_clients - clients_removed]->start();
            total_clients++;
        }

        clients_before = clients.size();
        clients.erase(std::remove_if(clients.begin(),
                clients.end(), isClientDone), clients.end());
        clients_after = clients.size();
        clients_removed += clients_before - clients_after;
    }
}



void Server::getChar() {
    char cmd;
    do {
        std::cin >> cmd;
    }while (cmd != 'q');
    done_accepting = true;
    bind_skt.close();
}

bool Server::doneAccepting() {
    return done_accepting;
}

Server::~Server() {}

