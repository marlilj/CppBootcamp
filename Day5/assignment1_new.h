#include<iostream>
#include <math.h>

class Shape {
protected:
    int a=0;
    int p=0;

public:
    Shape() = default;
    Shape(int _a, int _p):a(_a),p(_p) {}

    bool operator== (const Shape &s2);
    bool operator<= (const Shape &s2);
    bool operator>= (const Shape &s2);

    virtual int area()=0;
    virtual int perimeter()=0;

    void print() {
        std::cout << "Area: " << a <<std::endl;
        std::cout << "Perimeter: " << p <<std::endl;
    }
};

class Circle : public Shape {
private:
    int radius;
public:
    // Circle(int _r):radius(_r),Shape(this->area(),this->perimeter()) {}
    Circle(int _r);

    int area() override;
    int perimeter() override;
};

class Rectangle : public Shape {
private:
    int width;
    int height;
public:
    // Rectangle(int _w, int _h):width(_w),height(_h),Shape(this->area(),this->perimeter()) {}
    Rectangle(int _w, int _h);

    virtual int area() override;
    virtual int perimeter() override;
};

class Square : public Shape {
private:
    int width;
public:
    Square(int _w);//:width(_w),Shape(this->area(),this->perimeter()) {}

    int area() override;
    int perimeter() override;
};

class EquilateralTriangle : public Shape {
private:
    int width;
public:
    EquilateralTriangle(int _w);//:width(_w),Shape(this->area(),this->perimeter()) {}

    int area() override;
    int perimeter() override;
};