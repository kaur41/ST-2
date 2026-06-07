// src/tasks.cpp
#include "tasks.h"
#include "circle.h"
#include <cmath>

double earthRopeGap() {
    const double earthRadius = 6378100.0;  // 6378.1 км в метрах
    Circle earth(earthRadius);
    double oldFerence = earth.getFerence();
    earth.setFerence(oldFerence + 1.0);
    return earth.getRadius() - earthRadius;
}

double poolConcreteCost() {
    const double poolRadius = 3.0;
    const double pathWidth = 1.0;
    const double concretePrice = 1000.0;

    Circle pool(poolRadius);
    Circle outer(poolRadius + pathWidth);
    double pathArea = outer.getArea() - pool.getArea();
    return pathArea * concretePrice;
}

double poolFenceCost() {
    const double poolRadius = 3.0;
    const double pathWidth = 1.0;
    const double fencePrice = 2000.0;

    Circle outer(poolRadius + pathWidth);
    return outer.getFerence() * fencePrice;
}