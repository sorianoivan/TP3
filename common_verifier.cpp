#include "common_verifier.h"

#define MAX_NUM_2_BYTES 65535
#define MAX_NUM_3_DIGITS 999
#define MIN_NUM_3_DIGITS 100

Verifier::Verifier() {}

int Verifier::verifyNum(const unsigned int num) const {
    if (!_verifyRange(num)) return OUT_OF_RANGE;
    if (!_verifyRepeat(std::to_string(num))) return REPEATED_DIGIT;
    return 0;
}

int16_t Verifier::verifyCommand(const std::string& cmd) const  {
    int num;
    num = std::stoi(cmd);//esto va a tirar excepcion si no entra en 2 bytes
    if (num < 0 || num > MAX_NUM_2_BYTES)
        throw CommonException("Numero fuera de Rango");

    return num;
}

/* Verifica que el numero sea de 3 cifras */
bool Verifier::_verifyRange(const unsigned int num) const {
    return !(num < MIN_NUM_3_DIGITS || num > MAX_NUM_3_DIGITS);
}

/* Verifica que el numero no tenga cifras repetidas */
bool Verifier::_verifyRepeat(const std::string& num) const {
    char a = num.at(0);
    char b = num.at(1);
    char c = num.at(2);

    return !(a == b || a == c || b == c);
}

Verifier::~Verifier() {}
