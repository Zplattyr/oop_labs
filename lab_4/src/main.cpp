#include <iostream>
#include "collection.h"
#include "figure.h"
#include "pentagon.h"
#include "rhombus.h"
#include "trapezoid.h"
using namespace std;

int main(){

    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    point<double> a1{1.00005, 2.00005}, b1{3.00005, 2.00005}, c1{4.00005, 0.00005}, d1{0.00005, 0.00005};
    point<int> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    Collection<std::shared_ptr<Figure<double>>> arrt;
    Collection<std::shared_ptr<Figure<int>>> arrt2;
    std::initializer_list<point<double>> A1{a, b, c, d, e};
    std::initializer_list<point<double>> A2{a1, b1, c1, d1};
    std::initializer_list<point<int>> A3{a2, b2, c2, d4};
    
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Pentagon<double>>(A1);
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Trapezoid<double>>(A2);
    std::shared_ptr<Figure<int>> figure3 = std::make_shared<Rhombus<int>>(A3);
    arrt.pushBack(figure1);
    arrt.pushBack(figure2);
    arrt2.pushBack(figure3);
    cout << arrt;
    cout << arrt2;

    return 0;
}
