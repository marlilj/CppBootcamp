#include "../Day13/shape.h"

int main(int argc, char ** argv) {
    Circle c(10);
    Square s(10);
    Rectangle r(10,10);

    std::cout << (c==s) << std::endl;
}