#include "common_verifier.h"

Verifier::Verifier() {}

int Verifier::verifyNum(const int num) {
    if (!_verifyRange(num)) return OUT_OF_RANGE;
    if (!_verifyRepeat(std::to_string(num))) return REPEATED_DIGIT;
    return 0;
}

uint16_t Verifier::verifyCommand(const std::string& cmd) {
    int num;
    num = std::stoi(cmd);//esto va a tirar excepcion si no entra en 2 bytes
    if (num <= 0 || num > 65535) throw CommonException("Numero fuera de rango");

    return num;
}

/* Verifica que el numero sea de 3 cifras */
bool Verifier::_verifyRange(const int num) {
    return !(num < 100 || num > 999);
}

/* Verifica que el numero no tenga cifras repetidas */
bool Verifier::_verifyRepeat(const std::string& num) {
    char a = num.at(0);
    char b = num.at(1);
    char c = num.at(2);

    return !(a == b || a == c || b == c);
}

Verifier::~Verifier() {}
