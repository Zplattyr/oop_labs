#pragma once

#include <string>
#include <iostream>
#include "figure.h"
template <Number N>
class Trapezoid : public Figure<N>{
public :
    Trapezoid();
    
    Trapezoid(const std::initializer_list<point<N>> &dots);
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other);

protected :
    double calcArea() const override;
    bool equals(const Figure<N>& other) const override;
    void check() const override;
};

#include "trapezoid.hpp"
