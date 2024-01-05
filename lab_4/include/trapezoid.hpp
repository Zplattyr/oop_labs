#include "trapezoid.h"
#include <cmath>
template <Number N>
Trapezoid<N>::Trapezoid() : Figure<N>(4)
{
    this->tag = "TRAPEZOID";
};
template <Number N>
Trapezoid<N>::Trapezoid(const std::initializer_list<point<N>> &dots) : Figure<N>(dots, 4)
{
    this->tag = "TRAPEZOID";
    check();
};
template <Number N>
void Trapezoid<N>::check() const {
    if ((this->calcArea() == 0)) throw std::underflow_error("This is not a trapezoid");
    point<N> AB, BC, CD, DA;
    AB.x = this->arr[1].x - this->arr[0].x;
    AB.y = this->arr[1].y - this->arr[0].y;

    BC.x = this->arr[2].x - this->arr[1].x;
    BC.y = this->arr[2].y - this->arr[1].y;

    CD.x = this->arr[3].x - this->arr[2].x;
    CD.y = this->arr[3].y - this->arr[2].y;

    DA.x = this->arr[0].x - this->arr[3].x;
    DA.y = this->arr[0].y - this->arr[3].y;

    if (AB.x == 0 && CD.x == 0) {AB.x = AB.y; CD.x = CD.y;}
    if (AB.y == 0 && CD.y == 0) {AB.y = AB.x; CD.y = CD.x;}

    if (!(dbEqual(AB.x/CD.x, AB.y/CD.y))) throw std::underflow_error("This is not a trapezoid");
    if (dbEqual(BC.x/DA.x, BC.y/DA.y)) throw std::underflow_error("This is not a trapezoid");
    if (!(dbEqual(BC.len(), DA.len()))) throw std::underflow_error("This is not a correct trapezoid");
}
template <Number N>
Trapezoid<N>& Trapezoid<N>::operator=(const Trapezoid<N>& other)
{
    if (this != &other) {
        Figure<N>::operator=(other);
    }
    return *this;
}
template <Number N>
Trapezoid<N>& Trapezoid<N>::operator=(Trapezoid<N>&& other)
{
    if (this != &other) {
        Figure<N>::operator=(std::move(other));
    }
    return *this;
}
template <Number N>
double Trapezoid<N>::calcArea() const
{
    double a = distance(this->arr[0], this->arr[1]);
    double b = distance(this->arr[2], this->arr[3]);
    double c = distance(this->arr[1], this->arr[2]);
    double height = sqrt(pow(c, 2) - pow((b - a) / 2, 2));

    return (a + b) / 2 * height;
}
template <Number N>
bool Trapezoid<N>::equals(const Figure<N>& other) const {
    double a1 = distance(this->arr[0], this->arr[1]);
    double b1 = distance(this->arr[2], this->arr[3]);
    double c1 = distance(this->arr[1], this->arr[2]);
    double a2 = distance(other.getDots()[0], other.getDots()[1]);
    double b2 = distance(other.getDots()[2], other.getDots()[3]);
    double c2 = distance(other.getDots()[1], other.getDots()[2]);

    if (dbEqual(a1,a2) && dbEqual(b1,b2)
        && dbEqual(c1,c2))  
    return true;
    return false;
}
