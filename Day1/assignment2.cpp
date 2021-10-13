#include <iostream>

void decrypt(int key, std::string word);

int main() {
    // int key = 7;
    // std::string word = "OLSSV";
    // int key = 19;
    // std::string word = "VKRIMHZKTIAR";
    int key;
    std::string word;

    std::cout << "Enter a key between 0 and 26, and press enter...:" << std::endl;
    std::cin >> key;
    std::cout << std::endl;

    std::cout << "Enter chipher in only capital letters:" << std::endl;
    std::cin >> word;
    std::cout << std::endl;

    decrypt(key, word);
}

void decrypt(int key, std::string word) {
    for (char w: word) {
        char dw = w-key;
        int diff = dw - 'A';
        if (diff < 0) {
            dw = 'Z' + diff + 1;
        }
        std::cout << dw;
    }
    std::cout << std::endl;
}