#include "server_messenger.h"

#define AYUDA "Comandos válidos:\n\tAYUDA: despliega la lista de"\
" comandos válidos\n\tRENDIRSE: pierde el juego "\
"automáticamente\n\tXXX: Número de 3 cifras a ser"\
" enviado al servidor para adivinar el número secreto"

#define INVALID_NUM "Número inválido. Debe ser de 3"\
" cifras no repetidas"

#define LOST "Perdiste"

#define CMD_LEN 1
#define TEST_NUM_LEN 2
#define STRING_SIZE_LEN 4
#define TRIES_LIMIT 10

void Messenger::run() {
    char cmd;
    try {
        while (!isDone()) {
            cmd = _receiveCommand();
            _executeCommand(cmd);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool Messenger::isDone(){
    return (client_done || tries >= TRIES_LIMIT);
}

/* Recibe el byte que especifica el comando del cliente */
char Messenger::_receiveCommand() {
    char cmd;
    peer.receive(&cmd, CMD_LEN);
    return cmd;
}

/* Envia la respuesta al comando que me envio el cliente */
void Messenger::_executeCommand(char cmd) {
    switch (cmd) {
        case 'h':
            _sendResponse(AYUDA);
            break;
        case 's':
            client_done = true;
            _sendResponse(LOST);
            break;
        case 'n':
            _receiveNum();
            break;
        default:
            break;
    }
}

/* Recibe un numero del cliente, si es invalido le envia un mensaje,
 * si es valido lo compara y le envia el resultado */
void Messenger::_receiveNum(){
    uint16_t test_num = 0;
    ++tries;
    peer.receive(&test_num, TEST_NUM_LEN);
    test_num = ntohs(test_num);
    if (verifier.verifyNum(test_num) != 0) {
        _sendResponse(INVALID_NUM);
    } else {
        _compareNums(std::to_string(test_num));
    }
}

/* Compara el numero de prueba con el secreto y envia la respuesta al cliente*/
void Messenger::_compareNums(std::string test_num) {
    char test_digit;
    char secret_digit;
    int bien = 0, regular = 0;
    for (int i = 0; i < 3; ++i) {
        test_digit = test_num[i];
        for (int j = 0; j < 3; ++j) {
            secret_digit = std::to_string(secret_num)[j];
            if (secret_digit == test_digit) {
                if (i == j) bien++;
                else
                    regular++;
            }
        }
    }
    if (tries < TRIES_LIMIT || bien == 3)
        _sendResponse(bien, regular);
    else
        _sendResponse(LOST);
}

/* Arma la respuesta que hay que enviar al cliente
 * luego de comparar los numeros */
void Messenger::_buildResponse(unsigned short int bien,
                               unsigned short int regular,
                               std::stringstream& response){
    if (bien != 0 && regular != 0) {
        response << bien << " bien, " << regular << " regular" << std::endl;
    } else if (bien == 0 && regular == 0){
        response << "3 mal" << std::endl;
    } else if (bien == 0){
        response << regular << " regular" << std::endl;
    } else if (bien == 3){
        client_done = true;
        winners++;
        response << "Ganaste" << std::endl;
    } else {
        response << bien << " bien" << std::endl;
    }
}

/* Le envia al cliente el resultado de la comparacion de numeros */
void Messenger::_sendResponse(unsigned short int bien,
                              unsigned short int regular){
    uint32_t size;
    std::stringstream response;
    _buildResponse(bien, regular, response);
    size = response.str().size() - 1;// el -1 es para no mandar el \0
    size = htonl(size);
    peer.send(&size, STRING_SIZE_LEN);
    size = ntohl(size);
    //paso el stringstream a string y eso a char* ya que send
    // no soporta stringstream o string
    peer.send(response.str().c_str(), size);
}

/* Envia un mensaje al cliente como respuesta a un comando que no haya
 * sido un numero valido */
void Messenger::_sendResponse(const std::string& response) {
    uint32_t size;
    size = response.size();
    size = htonl(size);
    peer.send(&size, STRING_SIZE_LEN);
    peer.send(response.c_str(), response.size());
}

Messenger::~Messenger() {}
