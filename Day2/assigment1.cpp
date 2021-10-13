#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    std::uint32_t input_number;
    std::uint16_t size1, size2, size3;

    std::cout << "Enter a positive number and press enter..." << std::endl;
    std::cin >> input_number;

    std::cout << "Enter the size of the first dimension:" << std::endl;
    std::cin >> size1;
    std::cout << "Enter the size of the second dimension:" << std::endl;
    std::cin >> size2;
    std::cout << "Enter the size of the third dimension:" << std::endl;
    std::cin >> size3;

    std::uint32_t ***array; // 3D array definition

    array = new std::uint32_t**[size1]; // memory allocation first dim

    std::cout << "[" << std::endl;
    for (int i=0; i<size1; i++) {
        std::cout << "\t[" << std::endl;
        *(array+i) = new std::uint32_t*[size2]; // memory allocation second dim
        for (int j=0; j<size2; j++) {
            std::cout << "\t\t[";
            *(*(array+i)+j) = new std::uint32_t[size3];
            // array[i][j] = new std::uint32_t[size3];
            for (int k=0; k<size3; k++) {
                // array[i][j][k] = std::rand() % input_number; // allocation third dim
                *(*(*(array+i)+j)+k) = std::rand() % input_number; // allocation third dim
                std::cout << array[i][j][k];
                if (k < size3-1) {
                    std::cout << ",\t";
                }
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "\t]" << std::endl;
    }
    std::cout << "]" << std::endl;

    std::cout << "Deleting!" << std::endl;
    for (int i=0; i<size1; i++) {
        for (int j=0; j<size2; j++) {
            delete[] array[i][j];
        }
        delete[] *(array+i);
    }
    delete[] array;
    return 0;

}