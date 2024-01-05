#include "point.h"
#include <iomanip>
#include <cmath>

template <Number N>
bool dbEqual(N a, N b)
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}
template <Number N>
double point<N>::len() 
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
template <Number N>
bool point<N>::operator==(const point<N>& other) const
{
    if ((dbEqual(this->x, other.x)) && (dbEqual(this->y, other.y))) return true;
    return false;
}
template <Number N>
bool point<N>::operator!=(const point<N>& other) const
{
    if (*this == other) return false;
    return true;
}
template <Number N>
void point<N>::operator=(const point<N>& other)
{
    this->x = other.x;
    this->y = other.y;
}
template <Number N>
point<N> point<N>::operator+(const point<N>& other) const
{
    return point<N>{this->x + other.x, this->y + other.y};
}
template <Number N>
point<N> point<N>::operator-(const point<N>& other) const
{
    return point<N>{this->x - other.x, this->y - other.y};
}
template <Number N>
point<N> point<N>::operator+= (const point<N> &other) 
{
    *this = *this + other;
    return *this;
}
template <Number N>
point<N> point<N>::operator-= (const point<N> &other) 
{
    *this = *this - other;
    return *this;
}
template <Number N>
std::ostream& operator<<(std::ostream& out, const point<N>& _this)
{
    out << std::left << std::setw(12) << std::setprecision(7) << std::fixed <<_this.x << " | "  << std::setw(12) << _this.y << std::endl;
    return out;
}
template <Number N>
double distance(point<N> a, point<N> b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}
template <Number N>
bool point<N>::operator<(point<N>& other) {
    if (x < other.x) {
        return true;
    } else if (x == other.x) {
        return y < other.y;
    }
    return false;
}