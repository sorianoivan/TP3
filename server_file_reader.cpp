#include "server_file_reader.h"

FileReader::FileReader(std::string&& filename) {
    this->file.open(filename);
    if (!file.is_open()) throw CommonException("Error abriendo Archivo");
}

void FileReader::processFile(std::vector<int>& secret_nums) {
    int secret_num = 0;
    int flag;
    file.peek();//Para ver si el archivo esta vacio
    while (!file.eof()) {
        file >> secret_num;
        flag = verifier.verifyNum(secret_num);
        if (flag == OUT_OF_RANGE) throw CommonException
            ("Error: archivo con números fuera de rango");
        if (flag == REPEATED_DIGIT) throw CommonException
            ("Error: formato de los números inválidos");

        secret_nums.push_back(secret_num);
    }
    if (secret_nums.empty()) throw CommonException("El archivo esta vacio");
}

FileReader::~FileReader() {
    this->file.close();
}

void FileReader::operator()(std::vector<int>& secret_nums) {
    this->processFile(secret_nums);
}
