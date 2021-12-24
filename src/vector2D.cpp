#include<iostream>
#include<math.h>
#include"../include/vector2D.hpp"


Vector2D::Vector2D(){
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

float Vector2D::getLength(){
    return sqrt((x * x) + (y * y));
}

float Vector2D::getDistance(Vector2D v){
    return (*this - v).getLength();
}

Vector2D Vector2D::operator-(const Vector2D &other) const{
    Vector2D v = Vector2D(x - other.x, y - other.y);
    return v;
}

Vector2D Vector2D::operator-(const float other) const{
    return Vector2D(x - other, y - other);
}

Vector2D Vector2D::operator-(){
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D &other){
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator*(const float other){
    return Vector2D(x * other, y * other);
}

Vector2D Vector2D::operator/(const float other){
    return Vector2D(x / other, y / other);
}

void Vector2D::print(){
    std::cout << "[ " << this->x << ", " << this->y << " ]\n";
}