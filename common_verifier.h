#ifndef _NUMVERIFIER_H
#define _NUMVERIFIER_H

#define OUT_OF_RANGE -1
#define REPEATED_DIGIT -2

#include <string>

#include "common_exception.h"

class Verifier {
private:
public:
    /* Constructor */
    Verifier();
    /* Verifica si el numero es de 3 cifras y no estan repetidas */
    int verifyNum(const unsigned int num) const;
    /* Verifica que el comando enviado sea valido, es decir, un numero
     * que pueda ser representado con 2 bytes */
    uint16_t verifyCommand(const std::string& cmd) const;
    /* Destructor */
    ~Verifier();
private:
    bool _verifyRange(const unsigned int num) const;
    bool _verifyRepeat(const std::string& num) const;
};

#endif //_NUMVERIFIER_H
