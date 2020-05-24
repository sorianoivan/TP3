#ifndef _NUMVERIFIER_H
#define _NUMVERIFIER_H

#define OUT_OF_RANGE -1
#define REPEATED_DIGIT -2

#include <string>
#include "server_file_exception.h"

class Verifier {
private:
public:
    Verifier();
    int verifyNum(int num);
    uint16_t verifyCommand(std::string&& cmd);
    ~Verifier();
private:
    bool verifyRange(int num);
    bool verifyRepeat(std::string num);

};


#endif //_NUMVERIFIER_H
