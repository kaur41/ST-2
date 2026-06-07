

// Copyright 2025 UNN-CS
#include <gtest/gtest.h>
#include "circle.h"
#include "tasks.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ------------------ Тесты класса Circle ------------------

TEST(CircleTest, ConstructorAndGetters) {
    Circle c(5.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 5.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2.0 * M_PI * 5.0);
    EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 25.0);
}

TEST(CircleTest, SetRadiusUpdatesFerenceAndArea) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 3.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2.0 * M_PI * 3.0);
    EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 9.0);
}

TEST(CircleTest, SetFerenceUpdatesRadiusAndArea) {
    Circle c(1.0);
    double newFerence = 4.0 * M_PI;
    c.setFerence(newFerence);
    EXPECT_DOUBLE_EQ(c.getFerence(), newFerence);
    EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);      // L=4? ? R=2
    EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 4.0);
}

TEST(CircleTest, SetAreaUpdatesRadiusAndFerence) {
    Circle c(1.0);
    double newArea = 9.0 * M_PI;
    c.setArea(newArea);
    EXPECT_DOUBLE_EQ(c.getArea(), newArea);
    EXPECT_DOUBLE_EQ(c.getRadius(), 3.0);      // A=9? ? R=3
    EXPECT_DOUBLE_EQ(c.getFerence(), 2.0 * M_PI * 3.0);
}

TEST(CircleTest, ZeroRadius) {
    Circle c(0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetRadiusZero) {
    Circle c(5.0);
    c.setRadius(0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetFerenceZero) {
    Circle c(5.0);
    c.setFerence(0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetAreaZero) {
    Circle c(5.0);
    c.setArea(0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
}

TEST(CircleTest, ChainedSetRadius) {
    Circle c(2.0);
    c.setRadius(4.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 4.0);
    c.setRadius(1.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 1.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2.0 * M_PI);
    EXPECT_DOUBLE_EQ(c.getArea(), M_PI);
}

TEST(CircleTest, ChainedSetFerence) {
    Circle c(1.0);
    c.setFerence(2.0 * M_PI);  // R=1
    EXPECT_DOUBLE_EQ(c.getRadius(), 1.0);
    c.setFerence(4.0 * M_PI);  // R=2
    EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);
    EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 4.0);
}

TEST(CircleTest, ChainedSetArea) {
    Circle c(1.0);
    c.setArea(M_PI);           // R=1
    EXPECT_DOUBLE_EQ(c.getRadius(), 1.0);
    c.setArea(4.0 * M_PI);     // R=2
    EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 4.0 * M_PI);
}

TEST(CircleTest, Precision) {
    Circle c(1.0);
    c.setRadius(1.0/3.0);
    double expectedRadius = 1.0/3.0;
    EXPECT_NEAR(c.getRadius(), expectedRadius, 1e-12);
    EXPECT_NEAR(c.getFerence(), 2.0 * M_PI * expectedRadius, 1e-12);
    EXPECT_NEAR(c.getArea(), M_PI * expectedRadius * expectedRadius, 1e-12);
}

// ------------------ Тесты задачи "Земля и верёвка" ------------------

TEST(EarthRopeTest, GapPositive) {
    double gap = earthRopeGap();
    EXPECT_GT(gap, 0.0);
    // Теоретически зазор = 1/(2?) ? 0.159 м
    EXPECT_NEAR(gap, 1.0 / (2.0 * M_PI), 1e-9);
}

TEST(EarthRopeTest, GapIndependentOfRadius) {
    // Проверим, что зазор не зависит от начального радиуса (математически)
    double gap = earthRopeGap();
    // Создадим круг с другим радиусом и повторим логику вручную
    double testRadius = 1000.0;
    Circle testCircle(testRadius);
    double oldL = testCircle.getFerence();
    testCircle.setFerence(oldL + 1.0);
    double newR = testCircle.getRadius();
    double manualGap = newR - testRadius;
    EXPECT_NEAR(gap, manualGap, 1e-9);
}

// ------------------ Тесты задачи "Бассейн" ------------------

TEST(PoolTest, ConcreteCostPositive) {
    double cost = poolConcreteCost();
    EXPECT_GT(cost, 0.0);
    // Площадь дорожки: ?*(4^2 - 3^2) = ?*7 ? 21.991, стоимость ? 21991
    double expectedArea = M_PI * (16.0 - 9.0); // 7?
    double expectedCost = expectedArea * 1000.0;
    EXPECT_NEAR(cost, expectedCost, 1e-6);
}

TEST(PoolTest, FenceCostPositive) {
    double cost = poolFenceCost();
    EXPECT_GT(cost, 0.0);
    // Длина ограды: 2?*4 = 8? ? 25.133, стоимость ? 50265.48
    double expectedLength = 2.0 * M_PI * 4.0;
    double expectedCost = expectedLength * 2000.0;
    EXPECT_NEAR(cost, expectedCost, 1e-6);
}

TEST(PoolTest, ConcreteCostExact) {
    double cost = poolConcreteCost();
    // Точное значение: 1000 * ? * (4^2 - 3^2) = 1000 * ? * 7 = 7000?
    double exact = 7000.0 * M_PI;
    EXPECT_NEAR(cost, exact, 1e-6);
}

TEST(PoolTest, FenceCostExact) {
    double cost = poolFenceCost();
    // Точное значение: 2000 * 2?*4 = 2000 * 8? = 16000?
    double exact = 16000.0 * M_PI;
    EXPECT_NEAR(cost, exact, 1e-6);
}

// Дополнительные тесты для проверки независимости вычислений
TEST(PoolTest, ConcreteVsManual) {
    double r_inner = 3.0;
    double r_outer = 4.0;
    double areaPath = M_PI * (r_outer*r_outer - r_inner*r_inner);
    double expected = areaPath * 1000.0;
    EXPECT_DOUBLE_EQ(poolConcreteCost(), expected);
}

TEST(PoolTest, FenceVsManual) {
    double r_outer = 4.0;
    double length = 2.0 * M_PI * r_outer;
    double expected = length * 2000.0;
    EXPECT_DOUBLE_EQ(poolFenceCost(), expected);
}

// Проверка на использование класса Circle в задачах (косвенно)
TEST(PoolTest, CircleUsage) {
    Circle pool(3.0);
    Circle outer(4.0);
    double pathArea = outer.getArea() - pool.getArea();
    double concreteCost = pathArea * 1000.0;
    EXPECT_DOUBLE_EQ(concreteCost, poolConcreteCost());
}