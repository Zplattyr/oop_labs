#pragma once

#include <cmath>
#include <iostream>
#include <concepts>
#include <memory>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number N>
class point
{
public:
    N x;
    N y;
    
    template <Number _N>
    friend std::ostream& operator<<(std::ostream& out, const point<_N>& _this);
    double len();

    void operator=(const point& other);
    bool operator==(const point& other) const;
    bool operator!=(const point& other) const;
    point operator+(const point& other) const;
    point operator-(const point& other) const;
    point operator+= (const point &other);
    point operator-= (const point &other);
    bool operator<(point& other);
};

template <Number N>
bool dbEqual(N a, N b);


#include "point.hpp"