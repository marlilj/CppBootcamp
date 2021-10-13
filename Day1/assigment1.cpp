#include <iostream>
#include <stdlib.h>

int main() {
    std::uint32_t input_number;

    std::cout << "Enter a positive number and press enter..." << std::endl;
    std::cin >> input_number;

    std:uint32_t array[8][9][11];

    std::cout << "[" << std::endl;
    for (int i=0; i<8; i++) {
        std::cout << "\t[" << std::endl;
        for (int j=0; j<9; j++) {
            std::cout << "\t\t[";
            for (int k=0; k<11; k++) {
                array[i][j][k] = std::rand() % input_number;
                std::cout << array[i][j][k];
                if (k < 10) {
                    std::cout << ",\t";
                }
            }
            std::cout << "\t]" << std::endl;
        }
        std::cout << "\t]" << std::endl;
    }
    std::cout << "]" << std::endl;



}