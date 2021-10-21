#include <stdint.h>
#include <iostream>
#include <bitset>

typedef struct {
    std::bitset<5> seatBelts;
    std::bitset<3> lights;
    std::bitset<4> windows;
    std::bitset<4> doors;
} info_t;

void printInfo(const info_t &info) {

    // printing seat belts
    for (size_t i = 0; i < 5; i++) {
        std::cout << "Seat belt " << i+1 << " is ";
        if (info.seatBelts[i]) {
            std::cout << "fastened"<< std::endl;
        } else {
            std::cout << "open"<< std::endl;
        }
    }

    // printing windows
    for (size_t i = 0; i < 4; i++) {
        std::cout << "Window  " << i+1 << " is ";
        if (info.windows[i]) {
            std::cout << "opened"<< std::endl;
        } else {
            std::cout << "closed"<< std::endl;
        }
    }

    // printing doors
    for (size_t i = 0; i < 4; i++) {
        std::cout << "Door  " << i+1 << " is ";
        if (info.doors[i]) {
            std::cout << "open"<< std::endl;
        } else {
            std::cout << "closed"<< std::endl;
        }
    }

    // printing lights
    for (size_t i = 0; i < 4; i++) {
        std::cout << "Light  " << i+1 << " is ";
        if (info.seatBelts[i]) {
            std::cout << "on"<< std::endl;
        } else {
            std::cout << "off"<< std::endl;
        }
    }
}

info_t parseInput(const uint16_t &data) {

    info_t returnObject;

    uint16_t seatBeltMASK   = 0b1111100000000000;
    uint16_t windowsMASK    = 0b0000011110000000;
    uint16_t doorMASK       = 0b0000000001111000;
    uint16_t lightsMASK     = 0b0000000000000111;

    std::bitset<5> seatBelt = ((data & seatBeltMASK) >> 11);
    std::bitset<4> windows  = ((data & windowsMASK) >> 7);
    std::bitset<4> door     = ((data & doorMASK) >> 3 );
    std::bitset<3> lights   = (data & lightsMASK);

    std::cout << "Seat belts\t" << std::bitset<5>((data & seatBeltMASK) >> 11) << std::endl;
    std::cout << "Windows\t" << std::bitset<4>((data & windowsMASK) >> 7) << std::endl;
    std::cout << "Door\t" << std::bitset<4>((data & doorMASK) >> 3 ) << std::endl; 
    std::cout << "Lights\t" << std::bitset<3>(data & lightsMASK) << std::endl;

    returnObject.seatBelts = seatBelt;
    returnObject.windows = windows;
    returnObject.doors = door;
    returnObject.lights = lights;

    return returnObject;
}

int main(int argc, char ** argv) {

    uint16_t rawData = 0b1011101001011011;
    info_t data = parseInput(rawData);
    printInfo(data);

}