#include"assignment1.h"

bool Shape::operator==(const Shape &s2) {
    bool returnVal = false;
    s2.print();
    if (this->area() == s2.area()) {

    }
}

int Circle::area() {
    float r = (this->width)/2.0;
    return r*r*3; // pi = 3
}

int Circle::perimeter() {
    return this->width*3; // pi = 3
}

int main(int argc, char * argv[]) {

}