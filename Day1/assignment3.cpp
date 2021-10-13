#include <iostream>

int main() {
    std::string answer;
    bool lower;
    std::int64_t min = 1;
    std::int64_t max = 128;
    std::int64_t number = 128/2;

    std::cout << "Think about a number between 1 - 128 ...:" << std::endl;

    for (int i=0; i<7; i++) {
        std::cout << "Is the number lower than " << number << "? ( type correct if correct )" << std::endl;
        std::cin >> answer;

        if ("yes" == answer){
            lower = true;
        } else if ("correct" == answer) {
            std::cout << "You are thinking of number " << number << std::endl;
            break;
        } else {
            lower = false;
        }

        if (lower) {
            max = number;
        } else {
            min = number;
        }
        number = min + (max-min+1)/2;
    }
}