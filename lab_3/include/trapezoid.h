#pragma once

#include <string>
#include <iostream>
#include "figure.h"

class Trapezoid : public Figure{
public :
    Trapezoid();
    
    Trapezoid(const std::initializer_list<point> &dots);
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other);

protected :
    double calcArea() const override;
    bool equals(const Figure& other) const override;
    void constructFig(point &dot, double multiply);
    void check() const override;
};
