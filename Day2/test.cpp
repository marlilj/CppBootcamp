#include <iostream>

int main(int argc, char* argv[]) {
    std::string foo = "Hello World!";

    for (char &c: foo) {
        std::cout << c << std::endl;
    }

}