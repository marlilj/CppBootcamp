#include"shape.h"

bool Shape::operator==(const Shape &s2) {
    bool returnVal = false;
    if (this->a == s2.a && this->p == s2.p) {
        returnVal = true;
    }
    return returnVal;
}

bool Shape::operator<=(const Shape &s2) {
    bool returnVal = false;
    if (this->a < s2.a || (this->a == s2.a && this->p == s2.p)) {
        returnVal = true;
    }
    return returnVal;
}

bool Shape::operator>=(const Shape &s2) {
    bool returnVal = false;
    if (this->a > s2.a || (this->a == s2.a && this->p == s2.p)) {
        returnVal = true;
    }
    return returnVal;
}

Circle::Circle(int _r) {
    this->radius = _r;
    this->a = this->area();
    this->p = this->perimeter();
}

Rectangle::Rectangle(int _w, int _h) {
    this->width = _w;
    this->height = _h;
    this->a = this->area();
    this->p = this->perimeter();
}

Square::Square(int _w) {
    this->width = _w;
    this->a = this->area();
    this->p = this->perimeter();
}

EquilateralTriangle::EquilateralTriangle(int _w) {
    this->width = _w;
    this->a = this->area();
    this->p = this->perimeter();
}

int Circle::area() {
    return this->radius*this->radius*3; // pi = 3
}

int Circle::perimeter() {
    return this->radius*3; // pi = 3
}

int Rectangle::area() {
    return this->width*this->height;
}

int Rectangle::perimeter() {
    return 2*this->width+2*this->height;
}

int Square::area() {
    return this->width*this->width;
}

int Square::perimeter() {
    return 4*this->width;
}

int EquilateralTriangle::area() {
    int height = std::sqrt(3*std::pow(this->width,2)/4);
    return (this->width*height)/2;
}

int EquilateralTriangle::perimeter() {
    return 3*this->width;
}