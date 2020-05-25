#ifndef _COMMONSOCKET_H
#define _COMMONSOCKET_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "common_socket_exception.h"

class Socket {
private:
    int fd;

public:
    /* Constructor */
    Socket();
    /* Constructor por movimiento */
    Socket(Socket&& skt) noexcept;
    /* Constructor por copia anulado */
    Socket(const Socket& skt) = delete;

    /* Asignacion por movimiento */
    Socket& operator=(Socket&& skt) noexcept;
    /* Asignacion por copia borrada */
    Socket& operator=(const Socket& skt) = delete;

    /* Trata de establecer la conexion del socket bind del servidor.
     * Si falla lanza una excepcion */
    void setUpConnection(const char* port);
    /* Trata de establecer la conexion del cliente con el servidor.
     * Si falla lanza una excepcion */
    void setUpConnection(const char *host, const char *port);//client
    /* Devuelve el socket aceptado por el socket bind del serviddor*/
    Socket accept() const;
    /* Asigna a msg lo que recibe el socket. Si falla lanza una excepcion */
    int receive(void* msg, int len) const;
    /* Envia msg. Si falla lanza una excepcion */
    int send(const void *msg, int len) const;
    /* Devuelve el file descriptor del socket */
    int getFd() const;
    /* Cierra el socket */
    void close();
    /* Destructor */
    ~Socket();

private:
    explicit Socket(int fd);//Es privado ya que solo lo usa la funcion accept()
                            //para devolver un socket por movimiento
    void _setAddrInfo(struct addrinfo** results, const char* port);
    void _setAddrInfo(addrinfo **results, const char *host, const char *port);
    void _bind(addrinfo *results, int &skt);
    void _connect(addrinfo *results, int &skt);
};


#endif //_COMMONSOCKET_H
