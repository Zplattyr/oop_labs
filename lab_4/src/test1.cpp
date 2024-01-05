#include "point.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "trapezoid.h"
#include "collection.h"
#include <gtest/gtest.h>

TEST(test_01, create_test_set) {
    point<int> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    EXPECT_NO_THROW(Rhombus<int> ({a2, b2, c2, d4}));
}

TEST(test_02, create_test_set) {
    point<double> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    EXPECT_NO_THROW(Rhombus<double> ({a2, b2, c2, d4}));
}

TEST(test_03, create_test_set) {
    point<float> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    EXPECT_NO_THROW(Trapezoid<float> ({a1, b1, c1, d1}));
}

TEST(test_04, create_test_set) {
    point<double> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    EXPECT_NO_THROW(Trapezoid<double> ({a1, b1, c1, d1}));
}

TEST(test_05, create_test_set) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    EXPECT_NO_THROW((Pentagon<double> ({a, b, c, d, e})));
}

TEST(test_06, create_test_set) {
    point<float> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    EXPECT_NO_THROW((Pentagon<float> ({a, b, c, d, e})));
}

TEST(PointOperatorEqual, SamePointEquality) {
    point<double> p1 = {1.0, 2.0};
    point<double> p2 = {1.0, 2.0};
    EXPECT_TRUE(p1 == p2);
}

TEST(PointOperatorEqual, DifferentPointsInequality) {
    point<double> p1 = {1.0, 2.0};
    point<double> p2 = {3.0, 4.0};
    EXPECT_FALSE(p1 == p2);
}

TEST(PointOperatorLess, LessThan) {
    point p1 = {1.0, 2.0};
    point p2 = {3.0, 4.0};
    EXPECT_TRUE(p1 < p2);
}

TEST(PointOperatorLess, GreaterThan) {
    point p1 = {3.0, 4.0};
    point p2 = {1.0, 2.0};
    EXPECT_FALSE(p1 < p2);
}

TEST(PointDistance, CalculatingDistance) {
    point p1 = {0.0, 0.0};
    point p2 = {3.0, 4.0};
    EXPECT_DOUBLE_EQ(distance(p1, p2), 5.0);
}

TEST(Area, PENTAGON) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    Pentagon<double> P({a, b, c, d, e});
    std::cout << double(P);
    EXPECT_TRUE(dbEqual(double(P), 4.75528));
}

TEST(Area, TRAPEZOID) {
    point<double> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    Trapezoid<double> H({a1, b1, c1, d1});
    std::cout << double(H);
    EXPECT_TRUE(dbEqual(double(H), 6.0));
}

TEST(Area, RHOMBUS) {
    point<int> a2{1, 0}, b2{0, 1}, c2{-1, 0}, d2{0, -1};
    Rhombus<int> R({a2, b2, c2, d2});
    EXPECT_TRUE(dbEqual(double(R), 2.0));
}


TEST(FigureArray, AddAndRemoveFigures) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    point<double> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    point<int> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    Collection<std::shared_ptr<Figure<double>>> arrt;
    Collection<std::shared_ptr<Figure<int>>> arrt2;
    std::initializer_list<point<double>> A1 = {a, b, c, d, e};
    std::initializer_list<point<double>> A2 = {a1, b1, c1, d1};
    std::initializer_list<point<int>> A3 = {a2, b2, c2, d4};
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Pentagon<double>>(A1);
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Trapezoid<double>>(A2);
    std::shared_ptr<Figure<int>> figure3 = std::make_shared<Rhombus<int>>(A3);

    arrt.pushBack(figure1);
    arrt.pushBack(figure2);
    EXPECT_EQ(arrt.getSize(), 2);   
    arrt.remove(1);
    EXPECT_EQ(arrt.getSize(), 1);
}

TEST(FigureArray, SumAreas) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    point<double> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    point<double> a2{1, 0}, b2{0, 1}, c2{-1, 0}, d4{0, -1};
    Collection<std::shared_ptr<Figure<double>>> arrt;
    std::initializer_list<point<double>> A1 = {a, b, c, d, e};
    std::initializer_list<point<double>> A2 = {a1, b1, c1, d1};
    std::initializer_list<point<double>> A3 = {a2, b2, c2, d4};
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Pentagon<double>>(A1);
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Trapezoid<double>>(A2);
    std::shared_ptr<Figure<double>> figure3 = std::make_shared<Rhombus<double>>(A3);

    arrt.pushBack(figure1);
    arrt.pushBack(figure2);
    arrt.pushBack(figure3);
    double SUM = 6 + 2 + 4.75528;
    EXPECT_TRUE(dbEqual(arrt.getAllArea(), SUM));
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}