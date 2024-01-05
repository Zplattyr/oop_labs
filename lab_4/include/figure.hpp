#include "figure.h"
#include <cmath>
#include <iomanip>
template <Number N>
Figure<N>::Figure(): arr(Collection<point<N>>()), _size(0) {}
template <Number N>
Figure<N>::Figure(int n)
{
    _size = n;
    arr = Collection<point<N>>(n);
}
template <Number N>
Figure<N>::Figure(point<N> &center, int n)
{
    _center = center;
    _size = n;
    arr = Collection<point<N>>(n);
}
template <Number N>
Figure<N>::Figure(const std::initializer_list<point<N>> &dots, int n)
{
    arr = Collection<point<N>>(n);
    this->_size = n;
    if(dots.size() != n) throw std::underflow_error("Wrong quantity of numbers");
    size_t i = 0;

    for (auto &c : dots) { 
        arr[i++] = c;
        _center.x += arr[i - 1].x;
        _center.y += arr[i - 1].y;
    }

    _center.x /= n;
    _center.y /= n;
}
template <Number N>
Collection<point<N>> Figure<N>::getDots() const
{
    return arr;
}
template <Number N>
Figure<N>::~Figure() noexcept 
{
    _size = 0;
}
template <Number N>
point<N> Figure<N>::getGCenter() const{
    return _center;
}
template <Number N>
void Figure<N>::refreshCenter()
{
    point<N> center{0, 0};

    for (size_t i = 0; i < _size; i++)
    {
        center.x += arr[i].x;
        center.y += arr[i].y;
    }
    center.x /= _size;
    center.y /= _size;
    _center = center;
}
template <Number N>
const int Figure<N>::size() const
{
    return _size;
}
template <Number N>
const std::string Figure<N>::getTag() const
{
    return this->tag;
}
template <Number N>
void Figure<N>::constructFig(point<N> &dot, int n)
{
    double angle = degrE2Rad(360/n);
    double alfa = atan((_center.y - dot.y)/(_center.x - dot.x));
    double r = distance(_center, dot);
    for (size_t i = 0; i < n; i++)
    {
        arr[i].x = _center.x + (r * cos(alfa + (angle * i)));
        arr[i].y = _center.y + (r * sin(alfa + (angle * i)));
    }
}
template <Number N>
bool Figure<N>::trueFigCheck(int n) const
{
    double setDis = distance(arr[0], arr[n - 1]);
    double setR = distance(_center, arr[_size-1]);
    for (size_t i = 0; i < (_size - 1); i++)
    {
        double dis = distance(arr[i], arr[i+1]);
        double r = distance(_center, arr[i]);
        if (!(dbEqual(r, setR))) return false;
        if (!(dbEqual(dis, setDis))) return false;
    }
    return true;
}
template <Number N>
double Figure<N>::distance(point<N> a, point<N> b) const
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}
template <Number N>
double Figure<N>::degrE2Rad(N a) const
{
    return a * (M_PI / 180);
}
template <Number N>
bool Figure<N>::dbEqual(double a, double b) const
{
    double eps = 1e-5;
    return (fabs(a - b) < eps);
}
template <Number N>
double Figure<N>::calcArea() const
{
    return _size * pow(distance(_center, arr[0]), 2) * sin((2*M_PI)/_size) * 0.5;
}
template <Number N>
Figure<N>::operator double()
{
    return static_cast<double>(calcArea());
}
template <Number N>
bool Figure<N>::operator==(const Figure<N>& other) const
{
    if ((_size != other._size) || (this->tag != other.tag)) return false;
    if (!(equals(other))) return false;
    return true;
}
template <Number N>
Figure<N>& Figure<N>::operator=(const Figure<N>& other)
{
    if (*this == other) {
        return *this;
    }    
    _size  = other._size;
    arr = Collection<point<N>>(other._size);

    for(size_t i{0}; i < _size; ++i) arr[i] = other.arr[i];
    refreshCenter();
    return *this;
}

template <Number N>
Figure<N>& Figure<N>::operator=(Figure<N>&& other) noexcept
{
    if (this->tag != other.getTag());
    if (!(this == &other)) {
        arr = other.arr; 
        other.arr = nullptr;
    }
    refreshCenter();
    return *this;
}

template <Number N>
bool Figure<N>::equals(const Figure<N>& other) const
{
    double d1 = distance(this->arr[0], this->arr[1]);
    double d2 = distance(other.arr[0], other.arr[1]);
    if (!(dbEqual(d1, d2))) return false;
    return true;
}
template <Number N>
void Figure<N>::check() const {}
template <Number N>
std::ostream& operator<<(std::ostream& out, const Figure<N>& _this) //out overload
{
    std::cout << std::left << std::setw(13) << "X" << "| " << std::setw(13) << "Y" << std::endl; 
    for (size_t i = 0; i < _this._size; ++i) {
        out << _this.arr[i];
    }
    return out;
}
template <Number N>
std::istream& operator>>(std::istream& in, Figure<N>& _this)
{
    double value;
    _this.arr = new point<N>[_this._size];
    for (size_t i = 0; i < _this._size; i++)
    {
        in >> value;
        _this.arr[i].x = value;
        in >> value;
        _this.arr[i].y = value;
    }
    _this.refreshCenter();
    _this.check();
    return in;
}