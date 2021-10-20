#include <stdlib.h>
#include <iostream>

int main(int argc, char * argv[]) {

    // init
    int records[34] = {};
    int random_number;

    // assign a random value between [0,33] 10'000 times
    for (unsigned int i = 0; i < 10000; i++) {
        random_number = std::rand() % 34;
        records[random_number] = records[random_number] + 1;
    }

    // print in ascending order
    std::cout << "Number of occurences in ascending order" << std::endl;
    for (size_t i=0; i<34; i++) {
        std::cout << i << " occurs " << records[i] << " times" << std::endl;
    }

}