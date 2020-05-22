#include "Verifier.h"

Verifier::Verifier() {}

int Verifier::verifyNum(int num) {
    if(!verifyRange(num)) return OUT_OF_RANGE;
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

Verifier::~Verifier() {}