#include "pentagon.h"

Pentagon::Pentagon() : Figure(5)
{
    tag = "PENTAGON";
}

Pentagon::Pentagon(point &x, point &y) : Figure(x, 5)
{
    tag = "PENTAGON";
    constructFig(y, 5);
    check();
}

Pentagon::Pentagon(const std::initializer_list<point> &dots) : Figure(dots, 5)
{
    tag = "PENTAGON";
    check();
};

Pentagon& Pentagon::operator=(const Pentagon& other)
{
    if (this != &other) {
        Figure::operator=(other);
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other)
{
    if (this != &other) {
        Figure::operator=(std::move(other));
    }
    return *this;
}

bool Pentagon::equals(const Figure& other) const {
    double a = distance(arr[0], arr[1]);
    double b = distance(other.arr[0], other.arr[1]);
    return dbEqual(a,b);
}

void Pentagon::check() const
{
    if ((!(Figure::trueFigCheck(this->size())) || (this->calcArea() == 0))) throw std::underflow_error("This is not PENTAGON");
}