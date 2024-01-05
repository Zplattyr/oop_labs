#include "rhombus.h"
#include "figure.h"
#include <cmath>
template <Number N>
Rhombus<N>::Rhombus() : Figure<N>(4)
{
    this->tag = "RHOMBUS";
};
template <Number N>
Rhombus<N>::Rhombus(point<N> cen, point<N> dot, double multiply) : Figure<N>(cen, 4)
{
    this->tag = "RHOMBUS";
    constructFig(dot, multiply);
    check();
}
template <Number N>
Rhombus<N>::Rhombus(const std::initializer_list<point<N>> &dots) : Figure<N>(dots, 4)
{
    this->tag = "RHOMBUS";
    check();
};
template <Number N>
void Rhombus<N>::constructFig(point<N> &dot, double multiply)
{
    double angle = Figure<N>::degrE2Rad(360/4);
    double alfa = atan((dot.y - this->_center.y)/(dot.x - this->_center.x));
    double r = distance(this->_center, dot);
    double multi = 1;

    if ((1 < multiply) || (multiply < 0)) throw std::underflow_error("Multiply must be (0 < multiply < 1)");

    for (size_t i = 0; i < 4; i++)
    {
        if ((i % 2) == 0) {
            multi = 1;
        } else {
            multi = multiply;
        }
        this->arr[i].x = this->_center.x + (r * cos(alfa + (angle * i)) * multi);   
        this->arr[i].y = this->_center.y + (r * sin(alfa + (angle * i)) * multi);
    }                                   
}
template <Number N>
void Rhombus<N>::check() const
{
    if ((this->calcArea() == 0)) throw std::underflow_error("This is not a rhombus");
    int n = this->size();
    double setDis = distance(this->arr[0], this->arr[n - 1]);
    for (size_t i = 0; i < (n - 1); i++)
    {
        double dis = distance(this->arr[i], this->arr[i+1]);
        if (!(dbEqual(dis, setDis))) throw std::underflow_error("This is not a rhombus");
    }
}
template <Number N>
double Rhombus<N>::calcArea() const
{
    return distance(this->arr[1], this->arr[3]) * distance(this->arr[0], this->arr[2]) * 0.5;
}
template <Number N>
Rhombus<N>& Rhombus<N>::operator=(const Rhombus<N>& other)
{
    if (this != &other) {
        Figure<N>::operator=(other);
    }
    return *this;
}
template <Number N>
Rhombus<N>& Rhombus<N>::operator=(Rhombus<N>&& other)
{
    if (this != &other) {
        Figure<N>::operator=(std::move(other));
    }
    return *this;
}
template <Number N>
bool Rhombus<N>::equals(const Figure<N>& other) const
{
    double diagMain1 = distance(this->arr[0], this->arr[2]);
    double daigSub1 = distance(this->arr[1], this->arr[3]);

    double diagMain2 = distance(other.getDots()[0], other.getDots()[2]);
    double daigSub2 = distance(other.getDots()[1], other.getDots()[3]);

    if (!((dbEqual(diagMain1, diagMain2) && dbEqual(daigSub1, daigSub2)) || (dbEqual(diagMain1, daigSub2) && dbEqual(daigSub1, diagMain2))))
        return false;
    return true;
}
