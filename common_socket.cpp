#include "common_socket.h"

Socket::Socket() {
    this->fd = -1;
}

void Socket::_setAddrInfo(struct addrinfo** results, const char* port) {//server
    struct addrinfo hints;
    int flag;

    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    hints.ai_flags = AI_PASSIVE;

    flag = getaddrinfo(NULL, port, &hints, results);
    if (flag != 0){
        throw SocketException(gai_strerror(flag));
    }
}

void Socket::_setAddrInfo(struct addrinfo** results,const char* host, const char* port) {//server
    struct addrinfo hints;
    int flag;

    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    hints.ai_flags = 0;

    flag = getaddrinfo(host, port, &hints, results);
    if (flag != 0){
        throw SocketException(gai_strerror(flag));
    }
}

void Socket::_bind(struct addrinfo* results, int& skt) {
    struct addrinfo* current_result;
    bool connected = false;

    for (current_result = results; current_result != NULL
                                   && !connected;
         current_result = current_result->ai_next) {
        skt = socket(current_result->ai_family,
                     current_result->ai_socktype,
                     current_result->ai_protocol);
        if (skt == -1) {
            freeaddrinfo(results);
            throw SocketException(strerror(errno));
        }
        int val = 1;
        if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR,
                       &val, sizeof(val)) == -1) {
            freeaddrinfo(results);
            throw SocketException(strerror(errno));
        }
        if (bind(skt, current_result->ai_addr,
                 current_result->ai_addrlen) == -1) {
            freeaddrinfo(results);
            throw SocketException(strerror(errno));
        } else {
            connected = true;
        }
    }
    freeaddrinfo(results);
}

void Socket::setUpConnection(const char* port) {//server
    struct addrinfo *results;
    std::memset(&results, 0, sizeof(struct addrinfo *));

    _setAddrInfo(&results, port);

    _bind(results, this->fd);
}

void _connect(struct addrinfo* results, int& skt) {
    struct addrinfo* current_result;
    bool connected = false;

    for (current_result = results; current_result != NULL
                                   && !connected; current_result = current_result->ai_next) {
        skt = socket(current_result->ai_family,
                      current_result->ai_socktype, current_result->ai_protocol);
        if (skt == -1) {
            freeaddrinfo(results);
            throw SocketException(strerror(errno));
        }
        if (connect(skt, current_result->ai_addr,
                    current_result->ai_addrlen) == -1) {
            freeaddrinfo(results);
            throw SocketException(strerror(errno));//hacer freeaddrinfo antes de tirar exception
        } else {
            connected = true;
        }
    }
    freeaddrinfo(results);
}

void Socket::setUpConnection(const char* host, const char* port){//client
    struct addrinfo *results;
    memset(&results, 0, sizeof(struct addrinfo*));

    _setAddrInfo(&results, host, port);

    _connect(results, this->fd);
}

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket Socket::accept() {
    int peer_skt_fd;
    peer_skt_fd = ::accept(this->fd, NULL, NULL);
    if (peer_skt_fd == -1){
        throw SocketException(strerror(errno));
    }
    return Socket(peer_skt_fd);
}

int Socket::getFd() const {
    return this->fd;
}

int Socket::receive(void* msg, int len) const {
    int received = 0;
    int bytes_received = 0;

    while (bytes_received < len) {
        received = recv(this->fd, msg, len - bytes_received, 0);
        if (received == -1){
            throw SocketException(strerror(errno));//ver exception en thread
        }
        if (received == 0) return 0;//ver si esto es exception o no

        bytes_received += received;
    }
    return bytes_received;
}

int Socket::send(const void* msg, int msg_len) const{
    int bytes_sent = 0;
    int sent = 0;

    while (bytes_sent < msg_len) {
        sent = ::send(this->fd, msg, msg_len - bytes_sent, MSG_NOSIGNAL);
        if (sent == -1){
           throw SocketException(strerror(errno));
        }
        if (sent == 0) return 0;//ver si esto es exception o no
        bytes_sent += sent;
    }
    return bytes_sent;
}

Socket& Socket::operator=(Socket&& skt)  noexcept {
    this->fd = skt.fd;
    skt.fd = -1;
    return *this;
}

Socket::Socket(Socket &&skt) noexcept {
    this->fd = skt.fd;
    skt.fd = -1;//invalido el socket para q el que lo tenia antes no lo siga usando
}

Socket::~Socket() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}