#pragma once

#include <string>
#include <iostream>
#include "figure.h"
template <Number N>
class Rhombus: public Figure<N>{
public:
    Rhombus();
    Rhombus(point<N> x, point<N> y,  double multiply);
    Rhombus(const std::initializer_list<point<N>> &dots);
    Rhombus& operator=(Rhombus&& other);
    Rhombus& operator=(const Rhombus& other);
    
protected:
    double calcArea() const override;
    bool equals(const Figure<N>& other) const override;
    void constructFig(point<N> &dot, double multiply);
    void check() const override;
};

#include "rhombus.hpp"