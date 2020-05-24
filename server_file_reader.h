#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <string>
#include <fstream>

#include "common_verifier.h"
#include <vector>
#include <iostream>

class FileReader {
private:
    std::ifstream file;
    Verifier verifier;
public:
    explicit FileReader(std::string&& filename);
    void processFile(std::vector<int>& secret_nums);
    ~FileReader();
};


#endif //_FILEREADER_H
