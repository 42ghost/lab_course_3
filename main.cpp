#include <iostream>
#include "DES.cpp"

int main(){
    uint8_t key[9] = "ABCDef09";
    uint8_t input[1024];
    uint8_t enc[1024], dec[1024];

    std::cin >> input;
    int size = 0;
    while (input[size++] != '\0'){}
    size--;

    std::cout << "Input:\t\t";
    for (int i = 0; i < size; ++i){
        std::cout << (int)input[i] << ", ";
    }
    std::cout << std::endl;

    DES_Encryption DES;
    DES.encrypt(key, input, enc, size);
    std::cout << "Encrypted:\t";
    for (int i = 0; i < size; ++i){
        std::cout << (int)enc[i] << ", ";
    }
    std::cout << std::endl;


    DES.decrypt(key, enc, dec, size);
    std::cout << "Decrypted:\t";
    for (int i = 0; i < size; ++i){
        std::cout << (int)dec[i] << ", ";
    }
    std::cout << std::endl;
    
    return 0;
}
