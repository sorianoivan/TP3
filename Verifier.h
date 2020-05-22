#ifndef _NUMVERIFIER_H
#define _NUMVERIFIER_H

#define OUT_OF_RANGE -1
#define REPEATED_DIGIT -2

#include <string>
#include "FileException.h"

class Verifier {
private:
public:
    Verifier();
    int verifyNum(int num);
    bool verifyRange(int num);
    bool verifyRepeat(std::string num);
    ~Verifier();
};


#endif //_NUMVERIFIER_H
