#include "pentagon.h"
template <Number N>
Pentagon<N>::Pentagon() : Figure<N>(5)
{
    this->tag = "PENTAGON";
}
template <Number N>
Pentagon<N>::Pentagon(point<N> &x, point<N> &y) : Figure<N>(x, 5)
{
    this->tag = "PENTAGON";
    constructFig(y, 5);
    check();
}
template <Number N>
Pentagon<N>::Pentagon(const std::initializer_list<point<N>> &dots) : Figure<N>(dots, 5)
{
    this->tag = "PENTAGON";
    check();
};
template <Number N>
Pentagon<N>& Pentagon<N>::operator=(const Pentagon<N>& other)
{
    if (this != &other) {
        Figure<N>::operator=(other);
    }
    return *this;
}
template <Number N>
Pentagon<N>& Pentagon<N>::operator=(Pentagon<N>&& other)
{
    if (this != &other) {
        Figure<N>::operator=(std::move(other));
    }
    return *this;
}
template <Number N>
bool Pentagon<N>::equals(const Figure<N>& other) const {
    double a = distance(this->arr[0], this->arr[1]);
    double b = distance(other.getDots()[0], other.getDots()[1]);
    return dbEqual(a,b);
}
template <Number N>
void Pentagon<N>::check() const
{
    if ((!(Figure<N>::trueFigCheck(this->size())) || (this->calcArea() == 0))) throw std::underflow_error("This is not PENTAGON");
}