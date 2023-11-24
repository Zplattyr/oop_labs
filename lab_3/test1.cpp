#include "include/point.h"
#include "include/figure.h"
#include "include/rhombus.h"
#include "include/pentagon.h"
#include "include/trapezoid.h"
#include "include/fcollection.h"
#include "src/helper.cpp"
#include "src/point.cpp"
#include "src/figure.cpp"
#include "src/rhombus.cpp"
#include "src/pentagon.cpp"
#include "src/trapezoid.cpp"
#include "src/fcollection.cpp"
#include <gtest/gtest.h>

TEST(POINT, defaultConstructor)
{
    point a;
    point b{0, 0};
    EXPECT_TRUE(a == b);
}

TEST(POINT, II_IntConstructor)
{
    point b{4, 5};
    EXPECT_TRUE(((b.x == 4) && (b.y == 5)));
}

TEST(POINT, operatorEqual)
{
    point a{2, 2};
    point b{1, 1};
    EXPECT_TRUE(!(a == b));
}

TEST(POINT, operatorEqual2)
{
    point a{1, 0};
    point b{0, 1};
    EXPECT_TRUE(!(a == b));
}

TEST(POINT, operatorEqual3)
{
    point a{55, 2};
    point b{55, 2};
    EXPECT_TRUE((a == b));
}

TEST(POINT, operatorNotEqual)
{
    point a{2, 2};
    point b{1, 1};
    EXPECT_TRUE((a != b));
}

TEST(POINT, operatorNotEqual2)
{
    point a{1, 0};
    point b{0, 1};
    EXPECT_TRUE((a != b));
}

TEST(POINT, operatorNotEqual3)
{
    point a{55, 2};
    point b{55, 2};
    EXPECT_TRUE(!(a != b));
}

TEST(POINT, operatorCopy)
{
    point a{55, 2};
    point b{11, 4};
    b = a;
    EXPECT_TRUE(b == a);
}

TEST(POINT, doubleValue)
{
    point a{55.12345, 2.12345};
    point b{55.12345678, 2.12345788};
    EXPECT_TRUE(a == b);
}

TEST(POINT, doubleValue1)
{
    point a{55.12345, 2.12345};
    point b{55.12346678, 2.12345788};
    EXPECT_TRUE(a != b);
}

TEST(POINT, len)
{
    point a{3, 4};
    EXPECT_TRUE(a.len() == 5);
}

TEST(POINT, minus)
{
    point a{3, 4};
    point b{8, 10};
    EXPECT_TRUE(((a - b) == point{-5, -6}));
}

TEST(POINT, plus)
{
    point a{3, 4};
    point b{8, 10};
    EXPECT_TRUE(((a + b) == point{11, 14}));
}

TEST(PENTAGON, AllDotsConstructor)
{
    int flag = 0;
    double a1x = 100, a1y = 80, a2x = -30, a2y = -50;
    point b0, b1, b2, b3, b4;
    for (int i = 0; i < 40; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Pentagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];
        try
        {
            Pentagon B0({b0, b1, b2, b3, b4});
            Pentagon B1({b1, b2, b3, b4, b0});
            Pentagon B2({b2, b3, b4, b0, b1});
            Pentagon B3({b3, b4, b0, b1, b2});
            Pentagon B4({b4, b0, b1, b2, b3});
        }
        catch(const std::underflow_error& e)
        {
            flag += 1;
            break;
        }
    }

    EXPECT_TRUE(flag == 0);
}

TEST(PENTAGON, ZeroAreaFigure)
{
    point b0{1234, 456};

    EXPECT_THROW(Pentagon A({b0, b0, b0, b0, b0}), std::underflow_error);
}

TEST(PENTAGON, WrongDotsOrder)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];

    EXPECT_THROW(Pentagon A({b1, b0, b2, b3, b4}), std::underflow_error);
}

TEST(PENTAGON, WrongDots)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b4.x += 1;

    EXPECT_THROW(Pentagon A({b0, b1, b2, b3, b4}), std::underflow_error);
}

TEST(PENTAGON, tag)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});

    EXPECT_TRUE(B.getTag() == "PENTAGON");
}

TEST(PENTAGON, GCenter)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});

    EXPECT_TRUE(dbEqual(distance(B.getGCenter(), center), 0));
}


TEST(PENTAGON, operatorDouble_Aka_AREA)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{56, 78};
    Pentagon A(center, dot);
    double TrueArea =  5 * pow(distance(center, dot), 2) * sin((2*M_PI)/5) * 0.5;
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    EXPECT_TRUE(dbEqual(TrueArea, double(B)));
}

TEST(PENTAGON, operatorEqualTrue)
{
    int flag = 0;
    double a1x = 123, a1y = 45, a2x = -67, a2y = -89;
    point b0, b1, b2, b3, b4;
    for (int i = 0; i < 66; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Pentagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];

        Pentagon B0({b0, b1, b2, b3, b4});
        Pentagon B1({b1, b2, b3, b4, b0});
        Pentagon B2({b2, b3, b4, b0, b1});
        Pentagon B3({b3, b4, b0, b1, b2});
        Pentagon B4({b4, b0, b1, b2, b3});

        if (!((B0 == A) &&
              (B1 == A) &&
              (B2 == A) &&
              (B3 == A) &&
              (B4 == A) &&
              (B0 == B1) &&
              (B1 == B2) &&
              (B2 == B3) &&
              (B3 == B4) &&
              (B4 == B0) &&
              (B0 == B0))) {
                flag += 1;
                break;
              }

    }
    EXPECT_TRUE(flag == 0);
}

TEST(PENTAGON, operatorEqualTrue2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    EXPECT_TRUE(C == B);
}

TEST(PENTAGON, operatorEqualFalse)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1.05};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    EXPECT_TRUE(!(C == B));
}

TEST(PENTAGON, operatorEqualFalse2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3;
    c0 = point{1,2};
    c1 = point{3,2};
    c2 = point{4,0};
    c3 = point{0,0};
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{1, 0};
    Pentagon A1(center1, dot1);
    Trapezoid C({c0, c1, c2, c3});
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];


    Pentagon B({b0, b1, b2, b3, b4});
    EXPECT_TRUE(!(C == B));
}

TEST(PENTAGON, operatorCopy)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    Pentagon D({c0, c1, c2, c3, c4});
    C = B;

    EXPECT_TRUE(((!(B == D)) && (B == C)));
}

TEST(PENTAGON, operatorMove)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    Pentagon D({c0, c1, c2, c3, c4});
    B = std::move(C);

    EXPECT_TRUE(B == D);
}

TEST(RHOMBUS, AllDotsConstructor)
{
    int flag = 0;
    double a1x = 100, a1y = 80, a2x = -30, a2y = -50;
    point b0, b1, b2, b3, b4;
    for (int i = 0; i < 40; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Rhombus A(center, dot, 0.5);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        try
        {
            Rhombus B0({b0, b1, b2, b3});
            Rhombus B1({b1, b2, b3, b0});
            Rhombus B2({b2, b3, b0, b1});
            Rhombus B3({b3, b0, b1, b2});
            Rhombus B4({b0, b1, b2, b3});
        }
        catch(const std::underflow_error& e)
        {
            flag += 1;
            break;
        }
    }

    EXPECT_TRUE(flag == 0);
}

TEST(RHOMBUS, ZeroAreaFigure)
{
    point b0{1234, 456};

    EXPECT_THROW(Rhombus A({b0, b0, b0, b0}), std::underflow_error);
}

TEST(RHOMBUS, WrongDotsOrder)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Rhombus A(center, dot, 0.5);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];

    EXPECT_THROW(Rhombus A({b1, b0, b2, b3}), std::underflow_error);
}

TEST(RHOMBUS, WrongDots)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Rhombus A(center, dot, 0.5);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b3.x += 1;

    EXPECT_THROW(Rhombus A({b0, b1, b2, b3}), std::underflow_error);
}

TEST(RHOMBUS, tag)
{
    point b0, b1, b2, b3;
    point center{12, 34}, dot{-56, -78};
    Rhombus A(center, dot, 0.1);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    Rhombus B({b0, b1, b2, b3});

    EXPECT_TRUE(B.getTag() == "RHOMBUS");
}

TEST(RHOMBUS, GCenter)
{
    point b0, b1, b2, b3;
    point center{12, 34}, dot{-56, -78};
    Rhombus A(center, dot, 0.5);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    Rhombus B({b0, b1, b2, b3});

    EXPECT_TRUE(dbEqual(distance(B.getGCenter(), center), 0));
}


TEST(RHOMBUS, operatorDouble_Aka_AREA)
{
    point b0, b1, b2, b3;
    point center{12, 34}, dot{56, 78};
    double multi = 0.8;
    Rhombus A(center, dot, multi);
    double TrueArea =  (distance(center, dot) * 2) * (distance(center, dot) * 2 * multi * 0.5);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    EXPECT_TRUE(dbEqual(TrueArea, double(B)));
}

TEST(RHOMBUS, operatorEqualTrue)
{
    int flag = 0;
    double a1x = 123, a1y = 45, a2x = -67, a2y = -89;
    point b0, b1, b2, b3;
    for (int i = 0; i < 66; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Rhombus A(center, dot, 0.3);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];

        Rhombus B0({b0, b1, b2, b3});
        Rhombus B1({b1, b2, b3, b0});
        Rhombus B2({b2, b3, b0, b1});
        Rhombus B3({b3, b0, b1, b2});

        if (!((B0 == A) &&
              (B1 == A) &&
              (B2 == A) &&
              (B3 == A) &&
              (B0 == B1) &&
              (B1 == B2) &&
              (B2 == B3) &&
              (B3 == B0) &&
              (B0 == B0))) {
                flag += 1;
                break;
              }

    }
    EXPECT_TRUE(flag == 0);
}

TEST(RHOMBUS, operatorEqualTrue2)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1};
    Rhombus A1(center1, dot1, 0.789);
    Rhombus A2(center2, dot2, 0.789);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    Rhombus C({c0, c1, c2, c3});
    EXPECT_TRUE(C == B);
}

TEST(RHOMBUS, operatorEqualFalse)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1.05};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.5);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    Rhombus C({c0, c1, c2, c3});
    EXPECT_TRUE(!(C == B));
}

TEST(RHOMBUS, operatorEqualFalse2)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3, c4;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{1, 0};
    Rhombus A1(center1, dot1, 0.5);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    Rhombus B({b0, b1, b2, b3});
    Pentagon C({c0, c1, c2, c3, c4});
    EXPECT_TRUE(!(C == B));
}

TEST(RHOMBUS, operatorEqualFalse3)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{1, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    Rhombus C({c0, c1, c2, c3});
    EXPECT_TRUE(!(C == B));
}

TEST(RHOMBUS, operatorCopy)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.3);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    Rhombus C({c0, c1, c2, c3});
    Rhombus D({c0, c1, c2, c3});
    C = B;

    EXPECT_TRUE(((!(B == D)) && (B == C)));
}

TEST(RHOMBUS, operatorMove)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    Rhombus B({b0, b1, b2, b3});
    Rhombus C({c0, c1, c2, c3});
    Rhombus D({c0, c1, c2, c3});
    B = std::move(C);

    EXPECT_TRUE(B == D);
}

TEST(TRAPEZOID, AllDotsConstructor)
{
    int flag = 0;
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    for (int i = 0; i < 40; i++)
    {
        b0 += point{-i,i};
        b1 += point{i,i};
        b2 += point{i,-i};
        b3 += point{-i,-i};
        try
        {
            Trapezoid B0({b0, b1, b2, b3});
        }
        catch(const std::underflow_error& e)
        {
            flag += 1;
            break;
        }
    }

    EXPECT_TRUE(flag == 0);
}

TEST(TRAPEZOID, ZeroAreaFigure)
{
    point b0{1234, 456};

    EXPECT_THROW(Trapezoid A({b0, b0, b0, b0}), std::underflow_error);
}

TEST(TRAPEZOID, WrongDotsOrder)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};

    EXPECT_THROW(Trapezoid A({b0, b2, b1, b3}), std::underflow_error);
}

TEST(TRAPEZOID, WrongDots)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    b3.x += 1;

    EXPECT_THROW(Trapezoid A({b0, b1, b2, b3}), std::underflow_error);
}

TEST(TRAPEZOID, WrongDots2)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    b0.y += 1;

    EXPECT_THROW(Trapezoid A({b0, b1, b2, b3}), std::underflow_error);
}

TEST(TRAPEZOID, WrongDots3)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{1,2};
    b2 = point{3,0};
    b3 = point{0,0};

    EXPECT_THROW(Trapezoid A({b0, b1, b2, b3}), std::underflow_error);
}

TEST(TRAPEZOID, tag)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    Trapezoid B({b0, b1, b2, b3});

    EXPECT_TRUE(B.getTag() == "TRAPEZOID");
}


TEST(TRAPEZOID, operatorDouble_Aka_AREA)
{
    point b0, b1, b2, b3;
    double TrueArea =  (2 + 4) / 2 * 2;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    Trapezoid B({b0, b1, b2, b3});
    EXPECT_TRUE(dbEqual(TrueArea, double(B)));
}

TEST(TRAPEZOID, operatorEqualTrue)
{
    int flag = 0;
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    Trapezoid A({b0, b1, b2, b3});
    for (int i = 0; i < 66; i++)
    {
        b0 -= point{i,i};
        b1 -= point{i,i};
        b2 -= point{i,i};
        b3 -= point{i,i};

        Trapezoid B0({b0, b1, b2, b3});

        if (!(B0 == A)) {
                flag += 1;
                break;
              }

    }
    EXPECT_TRUE(flag == 0);
}

TEST(TRAPEZOID, operatorEqualFalse)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    
    c0 = point{0,2};
    c1 = point{4,2};
    c2 = point{5,0};
    c3 = point{-1,0};

    Trapezoid B({b0, b1, b2, b3});
    Trapezoid C({c0, c1, c2, c3});
    EXPECT_TRUE(!(C == B));
}

TEST(TRAPEZOID, operatorEqualFalse2)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    point center{0, 0}, dot{1, 0};
    Rhombus A1(center, dot, 0.5);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];

    c0 = point{1,2};
    c1 = point{3,2};
    c2 = point{4,0};
    c3 = point{0,0};
    Rhombus B({b0, b1, b2, b3});
    Trapezoid C({c0, c1, c2, c3});
    EXPECT_TRUE(!(C == B));
}

TEST(TRAPEZOID, operatorCopy)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    
    c0 = point{1,2};
    c1 = point{3,2};
    c2 = point{5,0};
    c3 = point{-1,0};
    Trapezoid B({b0, b1, b2, b3});
    Trapezoid C({c0, c1, c2, c3});
    Trapezoid D({c0, c1, c2, c3});
    C = B;

    EXPECT_TRUE(((!(B == D)) && (B == C)));
}

TEST(TRAPEZOID, operatorMove)
{
    int flag = 0;
    point b0, b1, b2, b3;
    point c0, c1, c2, c3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    
    c0 = point{1,2};
    c1 = point{3,2};
    c2 = point{5,0};
    c3 = point{-1,0};
    Trapezoid B({b0, b1, b2, b3});
    Trapezoid C({c0, c1, c2, c3});
    Trapezoid D({c0, c1, c2, c3});
    B = std::move(C);

    EXPECT_TRUE(B == D);
}


TEST(FCOLLECTION, pushBack)
{
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Pentagon A2(center2, dot2);
    Pentagon A3(center1, dot2);
    FigureCollection F;
    F.pushBack(&A1);
    F.pushBack(&A2);
    F.pushBack(&A3);

    EXPECT_TRUE((*F.get(0) == A1) && (*F.get(1) == A2) && (*F.get(2) == A3));
}

TEST(FCOLLECTION, pushBackMore)
{
    int flag = 0;
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Pentagon A2(center2, dot2);
    Trapezoid A3({b0, b1, b2, b3});
    FigureCollection F;
    try
    {
        F.pushBack(&A1);
        F.pushBack(&A2);
        F.pushBack(&A3);
        F.pushBack(&A1);
        F.pushBack(&A1);
        F.pushBack(&A3);
        F.pushBack(&A2);
        F.pushBack(&A2);
        F.pushBack(&A3);
    }
    catch(const std::underflow_error& e)
    {
        flag += 1;
    }

    EXPECT_TRUE(flag == 0);
}

TEST(FCOLLECTION, Remove)
{
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.2);
    FigureCollection F;
    F.pushBack(&A1);
    F.pushBack(&A2);

    F.remove(0);

    EXPECT_TRUE(*F.get(0) == A2);
}

TEST(FCOLLECTION, RemoveIndexError)
{
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.2);
    FigureCollection F;
    F.pushBack(&A1);
    F.pushBack(&A2);
    EXPECT_THROW(F.remove(2), std::underflow_error);
}

TEST(FCOLLECTION, GetIndexError)
{
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Rhombus A2(center2, dot2, 0.2);
    FigureCollection F;
    F.pushBack(&A1);
    F.pushBack(&A2);
    EXPECT_THROW(F.get(2), std::underflow_error);
}

TEST(FCOLLECTION, GetAllArea)
{
    point b0, b1, b2, b3;
    b0 = point{1,2};
    b1 = point{3,2};
    b2 = point{4,0};
    b3 = point{0,0};
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Rhombus A1(center1, dot1, 0.5);
    Pentagon A2(center2, dot2);
    Trapezoid A3({b0, b1, b2, b3});
    FigureCollection F;
    F.pushBack(&A1);
    F.pushBack(&A2);
    F.pushBack(&A3);
    EXPECT_TRUE(dbEqual(F.getAllArea(), double(A1) + double(A2) + double(A3)));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}