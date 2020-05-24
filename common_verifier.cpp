#include "common_verifier.h"

Verifier::Verifier() {}

int Verifier::verifyNum(int num) {
    if (!verifyRange(num)) return OUT_OF_RANGE;//Ver si tiro exception
    if (!verifyRepeat(std::to_string(num))) return REPEATED_DIGIT;
    return 0;
}

bool Verifier::verifyRange(int num) {
    return !(num < 100 || num > 999);
}

bool Verifier::verifyRepeat(std::string num) {
    char a = num.at(0);
    char b = num.at(1);
    char c = num.at(2);

    return !(a == b || a == c || b == c);
}

uint16_t Verifier::verifyCommand(std::string&& cmd) {
    int num;
    num = std::stoi(cmd);//esto va a tirar excepcion si no entra en 2 bytes
    if (num <= 0 || num > 65535) throw CommandException("");

    return num;
}

Verifier::~Verifier() {}
