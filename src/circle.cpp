// Copyright 2025 UNN-CS
#include "circle.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle::Circle(double radius) {
    setRadius(radius);
}

double Circle::getRadius() const {
    return radius_;
}

double Circle::getFerence() const {
    return ference_;
}

double Circle::getArea() const {
    return area_;
}

void Circle::setRadius(double radius) {
    radius_ = radius;
    ference_ = 2.0 * M_PI * radius_;
    area_ = M_PI * radius_ * radius_;
}

void Circle::setFerence(double ference) {
    ference_ = ference;
    radius_ = ference_ / (2.0 * M_PI);
    area_ = M_PI * radius_ * radius_;
}

void Circle::setArea(double area) {
    area_ = area;
    radius_ = std::sqrt(area_ / M_PI);
    ference_ = 2.0 * M_PI * radius_;
}