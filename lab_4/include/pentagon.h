#pragma once

#include "figure.h"
#include "point.h"
#include <string>
#include <iostream>

template <Number N>
class Pentagon: public Figure<N>{
public:
    Pentagon();
    Pentagon(point<N>& cen, point<N>& dot);
    Pentagon(const std::initializer_list<point<N>> &dots);
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other);
    bool equals(const Figure<N>&) const override;
    
protected:
    void check() const override;
};

#include "pentagon.hpp"