#include "trapezoid.h"
#include <cmath>

Trapezoid::Trapezoid() : Figure(4)
{
    tag = "TRAPEZOID";
};

Trapezoid::Trapezoid(const std::initializer_list<point> &dots) : Figure(dots, 4)
{
    tag = "TRAPEZOID";
    check();
};

void Trapezoid::check() const {
    if ((this->calcArea() == 0)) throw std::underflow_error("This is not a trapezoid");
    point AB, BC, CD, DA;
    AB.x = arr[1].x - arr[0].x;
    AB.y = arr[1].y - arr[0].y;

    BC.x = arr[2].x - arr[1].x;
    BC.y = arr[2].y - arr[1].y;

    CD.x = arr[3].x - arr[2].x;
    CD.y = arr[3].y - arr[2].y;

    DA.x = arr[0].x - arr[3].x;
    DA.y = arr[0].y - arr[3].y;

    if (AB.x == 0 && CD.x == 0) {AB.x = AB.y; CD.x = CD.y;}
    if (AB.y == 0 && CD.y == 0) {AB.y = AB.x; CD.y = CD.x;}

    if (!(dbEqual(AB.x/CD.x, AB.y/CD.y))) throw std::underflow_error("This is not a trapezoid");
    if (dbEqual(BC.x/DA.x, BC.y/DA.y)) throw std::underflow_error("This is not a trapezoid");
    if (!(dbEqual(BC.len(), DA.len()))) throw std::underflow_error("This is not a correct trapezoid");
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other)
{
    if (this != &other) {
        Figure::operator=(other);
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other)
{
    if (this != &other) {
        Figure::operator=(std::move(other));
    }
    return *this;
}

double Trapezoid::calcArea() const
{
    double a = distance(arr[0], arr[1]);
    double b = distance(arr[2], arr[3]);
    double c = distance(arr[1], arr[2]);
    double height = sqrt(pow(c, 2) - pow((b - a) / 2, 2));

    return (a + b) / 2 * height;
}

bool Trapezoid::equals(const Figure& other) const {
    double a1 = distance(arr[0], arr[1]);
    double b1 = distance(arr[2], arr[3]);
    double c1 = distance(arr[1], arr[2]);
    double a2 = distance(other.getDots()[0], other.getDots()[1]);
    double b2 = distance(other.getDots()[2], other.getDots()[3]);
    double c2 = distance(other.getDots()[1], other.getDots()[2]);

    if (dbEqual(a1,a2) && dbEqual(b1,b2)
        && dbEqual(c1,c2))  
    return true;
    return false;
}
