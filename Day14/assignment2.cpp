#include <stdint.h>
#include <iostream>
#include <bitset>

typedef struct {
    unsigned int speed;
    unsigned int front;
    unsigned int rear;
    unsigned int right; 
    unsigned int left;
} info_t;

uint16_t encodeData(unsigned int speed, unsigned int front, unsigned int rear, unsigned int right, unsigned int left) {
    uint16_t encodedData;

    if (speed > 300) {
        speed = 300;
        std::cout << "Max speed is 300" << std::endl;
    }

    if (front > 1050) {
        front = 1050;
        std::cout << "Maximum distance to measure in front is 1050" << std::endl;
    }

    if (rear > 1050) {
        rear = 1050;
        std::cout << "Maximum distance to measure in rear is 1050" << std::endl;
    }

    if (right > 1050) {
        right = 1050;
        std::cout << "Maximum distance to measure in right is 1050" << std::endl;
    }

    if (left > 1050) {
        left = 1050;
        std::cout << "Maximum distance to measure in left is 1050" << std::endl;
    }

    std::bitset<16> bitSpeedInput(speed / 20);
    std::bitset<16> bitFrontInput(front / 150);
    std::bitset<16> bitRearInput(rear / 150);
    std::bitset<16> bitRightInput(right / 150);
    std::bitset<16> bitLeftInput(left / 150);
    // std::cout << std::bitset<16>(bitSpeedInput) << std::endl;
    // std::cout << std::bitset<16>(bitFrontInput) << std::endl;
    // std::cout << std::bitset<16>(bitRearInput) << std::endl;
    // std::cout << std::bitset<16>(bitRightInput) << std::endl;
    // std::cout << std::bitset<16>(bitLeftInput) << std::endl;

    std::bitset<16> bitSpeed   = (bitSpeedInput) << 12;
    std::bitset<16> bitFront   = bitFrontInput << 9;
    std::bitset<16> bitRear    = bitRearInput << 6;
    std::bitset<16> bitRight   = bitRightInput << 3;
    std::bitset<16> bitLeft    = bitLeftInput;
    // std::cout << std::bitset<16>(bitSpeed) << std::endl;
    // std::cout << std::bitset<16>(bitFront) << std::endl;
    // std::cout << std::bitset<16>(bitRear) << std::endl;
    // std::cout << std::bitset<16>(bitRight) << std::endl;
    // std::cout << std::bitset<16>(bitLeft) << std::endl;

    encodedData = (bitSpeed.to_ulong() | bitFront.to_ulong() | bitRear.to_ullong() | bitRight.to_ullong() | bitLeft.to_ullong());

    return encodedData;

}

info_t parseInput(const uint16_t &data) {

    info_t returnObject;

    uint16_t speedMASK   = 0b1111000000000000;
    uint16_t frontMASK   = 0b0000111000000000;
    uint16_t rearMASK    = 0b0000000111000000;
    uint16_t rightMASK   = 0b0000000000111000;
    uint16_t leftMASK    = 0b0000000000000111;

    std::bitset<4> bitSpeed   = (data & speedMASK) >> 12;
    std::bitset<3> bitFront   = (data & frontMASK) >> 9;
    std::bitset<3> bitRear    = (data & rearMASK) >> 6;
    std::bitset<3> bitRight   = (data & rightMASK) >> 3;
    std::bitset<3> bitLeft    = (data & leftMASK);

    float speed   = bitSpeed.to_ulong() * 20;
    float front   = bitFront.to_ulong() * 150;
    float rear    = bitRear.to_ulong() * 150;
    float right   = bitRight.to_ulong() * 150;
    float left    = bitLeft.to_ulong() * 150;

    returnObject.speed = speed;
    returnObject.front = front;
    returnObject.rear  = rear;
    returnObject.right = right;
    returnObject.left  = left;

    return returnObject;
}

void printInfo(const info_t &info) {
    std::cout << "speed\t" << info.speed << std::endl;
    std::cout << "front\t" << info.front << std::endl;
    std::cout << "rear\t" << info.rear << std::endl; 
    std::cout << "right\t" << info.right << std::endl;
    std::cout << "left\t" << info.left << std::endl;
}

int main(int argc, char ** argv) {

    info_t initData;
    initData.speed=300;
    initData.front=900;
    initData.rear=750;
    initData.right=600;
    initData.left=900;
    std::cout << "INIT" << std::endl;
    printInfo(initData);

    uint16_t encodedData = encodeData(initData.speed, initData.front, initData.rear, initData.right, initData.left);
    info_t info = parseInput(encodedData);
    std::cout << "DECODED" << std::endl;
    printInfo(info);

}