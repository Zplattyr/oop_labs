#include "point.h"
#include <iomanip>
#include <cmath>

bool point::dbEqual(double a, double b) const
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}

double point::len() const
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

bool point::operator==(const point& other) const
{
    if ((dbEqual(this->x, other.x)) && (dbEqual(this->y, other.y))) return true;
    return false;
}

bool point::operator!=(const point& other) const
{
    if (*this == other) return false;
    return true;
}

void point::operator=(const point& other)
{
    this->x = other.x;
    this->y = other.y;
}

point point::operator+(const point& other) const
{
    return point{this->x + other.x, this->y + other.y};
}

point point::operator-(const point& other) const
{
    return point{this->x - other.x, this->y - other.y};
}

point point::operator+= (const point &other) 
{
    *this = *this + other;
    return *this;
}

point point::operator-= (const point &other) 
{
    *this = *this - other;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const point& _this)
{
    out << std::left << std::setw(12) << std::setprecision(7) << std::fixed <<_this.x << " | "  << std::setw(12) << _this.y << std::endl;
    return out;
}