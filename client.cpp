#include "client.h"


#define STRING_SIZE_LEN 4

Client::Client() {}

void Client::run(const char* host, const char* port) {
    client_skt.setUpConnection(host, port);
    _guessNumber();
}

/* Recibe comandos por entrada estandar y
 * los ejecuta hasta que gane o pierda la partida */
void Client::_guessNumber() {
    std::string cmd;
    int received = -1;
    int sent;
    do {
        std::cin >> cmd;
        sent = _executeCommand(cmd);
        if (sent != 0)//Si el comando es invalido no envio nada por lo que no
                      // espero una respuesta
            received = _receiveResponse();
    }while (received != 0);
}

/* Si el comando es valido, envia el mensaje correspondiente al servidor */
int Client::_executeCommand(const std::string& cmd){
    if (cmd == "AYUDA") {
        return _sendMessage('h');
    } else if (cmd == "RENDIRSE") {
        return _sendMessage('s');
    } else {
        int16_t num = -1;
        try { //Si el comando es invalido tengo que agarrar la excepcion
            num = verifier.verifyCommand(cmd);
        } catch (std::exception& e) {
            std::cout << "Error: comando inválido. "
                         "Escriba AYUDA para obtener ayuda" << std::endl;
        }
        if (num != -1) return _sendMessage(num);
    }
    return 0;
}

/* Envia al servidor el numero para que lo compare con el secreto
 * siguiendo el protocolo especificado*/
int Client::_sendMessage(int16_t num) {
    char to_send = 'n';
    client_skt.send(&to_send, 1);
    num = htons(num);
    return client_skt.send(&num, 2);
}

/* Le envia el comando al servidor pidiendo ayuda o rindiendose
 * siguiendo el protocolo especificado */
int Client::_sendMessage(const char to_send) {
    return client_skt.send(&to_send, 1);
}

/* Recibe la respuesta del servidor siguiendo el protocolo especificado.
 * Uso char* en vez de std::vector<char> ya que la funcion recv de sockets
 * recibe void* y no soporta std::vector */
int Client::_receiveResponse(){
    char* response;
    uint32_t len = 0;
    int received = client_skt.receive(&len, STRING_SIZE_LEN);
    len = ntohl(len);
    response = new char[len + 2];
    client_skt.receive(response, len);
    response[len] = '\n';
    response[len + 1] = '\0';
    std::cout << response;
    if (!strncmp(response, "Perdiste", 8) || !strncmp(response, "Ganaste", 7))
        received = 0;
    delete [] response;
    return received;
}

Client::~Client() {}
