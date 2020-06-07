#include "common_socket.h"

#define MAX_LISTENERS 10

Socket::Socket() {
    this->fd = -1;
}

Socket::Socket(Socket &&skt) noexcept {
    this->fd = skt.fd;
    skt.fd = -1;//invalido el socket para q el
    // que lo tenia antes no lo siga usando
}

Socket& Socket::operator=(Socket&& skt)  noexcept {
    this->fd = skt.fd;
    skt.fd = -1;
    return *this;
}

void Socket::setUpConnection(const char* port) {//server
    struct addrinfo *results;
    std::memset(&results, 0, sizeof(struct addrinfo *));

    _setAddrInfo(&results, port);

    _bind(results, this->fd);
}

void Socket::setUpConnection(const char* host, const char* port){//client
    struct addrinfo *results;
    memset(&results, 0, sizeof(struct addrinfo*));

    _setAddrInfo(&results, host, port);

    _connect(results, this->fd);
}

void Socket::listen() {
    if (::listen(this->fd, MAX_LISTENERS) == -1)
        throw SocketException(strerror(errno));
}

Socket Socket::accept() const {
    int peer_skt_fd;
    peer_skt_fd = ::accept(this->fd, NULL, NULL);
    if (peer_skt_fd == -1){
        throw SocketException(strerror(errno));
    }
    return Socket(peer_skt_fd);
}

int Socket::receive(void* msg, const int len) const {
    int received;
    int bytes_received = 0;

    while (bytes_received < len) {
        received = recv(this->fd, msg, len - bytes_received, 0);
        if (received == -1){
            throw SocketException(strerror(errno));
        }
        if (received == 0) return 0;

        bytes_received += received;
    }
    return bytes_received;
}

int Socket::send(const void* msg, int len) const{
    int bytes_sent = 0;
    int sent = 0;

    while (bytes_sent < len) {
        sent = ::send(this->fd, msg, len - bytes_sent, MSG_NOSIGNAL);
        if (sent == -1){
            throw SocketException(strerror(errno));
        }
        if (sent == 0) return 0;
        bytes_sent += sent;
    }
    return bytes_sent;
}

int Socket::getFd() const {
    return this->fd;
}

Socket::Socket(int fd) {
    this->fd = fd;
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

void Socket::_setAddrInfo(struct addrinfo** results, const char* host,
                          const char* port) {//client
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
/* Mas de 20 lineas por que muchas lineas tienen que ser separadas en varias
 * para no superar el limite de 80 caracteres y ademas hay varios
 * chequeos de error */
void Socket::_bind(struct addrinfo* results, int& skt) {
    struct addrinfo* current_result;
    bool connected = false;

    for (current_result = results; current_result != NULL && !connected;
                                current_result = current_result->ai_next) {
        skt = socket(current_result->ai_family, current_result->ai_socktype,
                                                current_result->ai_protocol);
        if (skt == -1) {
            std::cerr << strerror(errno) << std::endl;
        } else {
            int val = 1;
            if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR,
                           &val, sizeof(val)) == -1) {
                std::cerr << strerror(errno) << std::endl;
                ::close(skt);
            } else {
                if (bind(skt, current_result->ai_addr,
                         current_result->ai_addrlen) == -1) {
                    std::cerr << strerror(errno) << std::endl;
                    ::close(skt);
                } else {
                    connected = true;
                }
            }
        }
    }
    freeaddrinfo(results);

    if (!connected) throw SocketException("Could not bind");
}

/* Idem _bind() */
void Socket::_connect(struct addrinfo* results, int& skt) {
    struct addrinfo* current_result;
    bool connected = false;

    for (current_result = results; current_result != NULL
                                   && !connected; current_result =
                                           current_result->ai_next) {
        skt = socket(current_result->ai_family,
                      current_result->ai_socktype,
                      current_result->ai_protocol);
        if (skt == -1) {
            std::cout << strerror(errno) << std::endl;
        } else {
            if (connect(skt, current_result->ai_addr,
                        current_result->ai_addrlen) == -1) {
                std::cout << strerror(errno) << std::endl;
                ::close(skt);
            } else {
                connected = true;
            }
        }
    }
    freeaddrinfo(results);
    if (!connected) throw SocketException("Could not connect");
}

void Socket::close() {
    shutdown(this->fd, SHUT_RDWR);
    ::close(this->fd);
}

Socket::~Socket() {
    if (fd != -1) {
        this->close();
    }
}
