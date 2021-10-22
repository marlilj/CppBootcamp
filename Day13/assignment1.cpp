#include"shape.h"

template <typename T1, typename T2>
void compare(T1 &_t1, T2 &_t2) {
    if (_t1 == _t2) {
        std::cout << "EQUAL" << std::endl;
    } else if (_t1 >= _t2) {
        std::cout << "LARGER THAN OR EQUAL" << std::endl;
    } else {
        std::cout << "LESS THAN OR EQUAL" << std::endl;
    }
}

// Specialization of sum for struct Shape
template<>
void compare<Shape, Shape>(Shape &_t1, Shape &_t2) {
    std::cout << "FIRST:" << std::endl;
    _t1.print();
    std::cout << "SECOND:" << std::endl;
    _t2.print();
    std::cout << std::endl;
    if (_t1 == _t2) {
        std::cout << "FIRST EQUALS SECOND" << std::endl;
    } else if (_t1 >= _t2) {
        std::cout << "FIRST IS LARGER THAN OR EQUAL TO SECOND" << std::endl;
    } else {
        std::cout << "FIRST IS LESS THAN OR EQUAL TO SECOND" << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char * argv[]) {

    Circle c(10);
    Square s(10);
    Rectangle r(10,10);
    Shape *shape_circle = new Circle(12);
    Shape *shape_square = new Square(14);
    compare<Shape,Shape>(r,s);
    compare(*shape_circle, *shape_square);

    delete shape_square;
    delete shape_circle;
    // c.print();
    // s.print();
    // r.print();

    // r == s;

    // c <= s;

    // c >= s;

}