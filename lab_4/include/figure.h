#pragma once

#include "point.h"
#include "collection.h"
#include <string>
#include <iostream>

template <Number N>
class Figure
{ 
public:
    virtual ~Figure() noexcept;

    const std::string getTag() const;
    const int size() const;

    point<N> getGCenter() const;
    Collection<point<N>> getDots() const;

    operator double();
    Figure<N>& operator=(const Figure<N>& other);
    Figure<N>& operator=(Figure<N>&& other) noexcept;
    bool operator==(const Figure<N>& other) const;
    template<Number _N>
    friend std::ostream& operator<<(std::ostream &stream, const Figure<_N>&  Figure);
    template<Number N_>
    friend std::istream& operator>>(std::istream &stream, Figure<N_>& Figure);
    
protected:
    Figure();
    Figure(int n);
    Figure(point<N> &center, int n);
    Figure(const std::initializer_list<point<N>> &dots, int n);

    virtual void check() const;
    virtual bool equals(const Figure<N>& other) const;
    virtual double calcArea() const;

    bool trueFigCheck(int n) const;
    bool dbEqual(double a, double b) const;
    void refreshCenter();
    void constructFig(point<N> &dot, int n);

    double distance(point<N> a, point<N> b) const;
    double degrE2Rad(N a) const;

    std::string tag = "NULL";
    Collection<point<N>> arr;
    point<N> _center;
private:
    size_t _size = 2;
};

#include "figure.hpp"