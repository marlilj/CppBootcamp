#include<iostream>

class Shape {
protected:
    int width;

public:
    Shape::Shape() = delete;
    Shape::Shape(int _w):width(_w) {}

    bool operator== (const Shape &s2);
    bool operator<= (const Shape &s2);
    bool operator>= (const Shape &s2);

    virtual int area()=0;
    virtual int perimeter()=0;

    void print() {
        std::cout << "Area: " << this->area() <<std::endl;
        std::cout << "Perimeter: " << this->perimeter() <<std::endl;
    }
};

class Circle : public Shape {
public:
    Circle::Circle(int diameter):Shape(diameter){};

    int area() override {};
    int perimeter() override {};
};

class Rectangle : public Shape {
private:
    int height;
public:
    Rectangle::Rectangle(int _w, int _h):Shape(_w),height(_h){};

    virtual int area() override {};
    virtual int perimeter() override {};
};

class Square : public Rectangle {
public:
    Square::Square(int _w):Rectangle(_w,_w){};

    int area() override {};
    int perimeter() override {};
};

class EquilateralTriangle : public Rectangle {
public:
    EquilateralTriangle::EquilateralTriangle(int _w):Rectangle(_w,_w){};

    int area() override {};
    int perimeter() override {};
};