#include "FileReader.h"

FileReader::FileReader(std::string&& filename) {
    this->file.open(filename);
    if (!file.is_open()) throw FileException("Error abriendo Archivo");
}

void FileReader::processFile(std::vector<int>& secret_nums) {
    int secret_num = 0;
    int flag = 0;
    file.peek();
    while (!file.eof()) {
        file >> secret_num;
        flag = verifier.verifyNum(secret_num);
        if (flag == OUT_OF_RANGE) throw FileException
            ("Error: archivo con números fuera de rango");
        if (flag == REPEATED_DIGIT) throw FileException
            ("Error: formato de los números inválidos");

        secret_nums.push_back(secret_num);
    }
    if (secret_nums.empty()) throw FileException("El archivo esta vacio");
}

FileReader::~FileReader() {
    this->file.close();
}
