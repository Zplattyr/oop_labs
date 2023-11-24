#include <iostream>
#include "src/helper.cpp"
#include "fcollection.h"
#include "figure.h"
#include "pentagon.h"
#include "rhombus.h"
#include "trapezoid.h"
using namespace std;

int main(){

        point center1{0, 0}, center2{123, 456};
        point dot1{1, 1}, dot2{9.8, 6.5}, dot3{987, 321};
        point b0, b1, b2, b3;
        b0 = point{1,2};
        b1 = point{3,2};
        b2 = point{4,0};
        b3 = point{0,0};
        Pentagon P(center1, dot1);
        Trapezoid T({b1, b0, b2, b3});
        Rhombus R(center2, dot3, 0.123);

        Pentagon Pinput;
        Trapezoid Tinput;
        Rhombus Rinput;

        cout << " V Pentagon for your input V\n";
        cout << P;
        cout << "Or just copy this: 1.00000 1.00000 -0.64204 1.26007 -1.39680 -0.22123 -0.22123 -1.39680 1.26007 -0.64204\n";
        cout << "Input dots: ";
        cin >> Pinput;
        cout << "Equal Figures: " << (P == Pinput) << "\n";
        cout << "Wanna skip other inputs? (Y/N)\n";
        char c;
        cin >> c;
        if (c == 'Y'){
            Tinput = T;
            Rinput = R;
        } else {
            cout << " V Trapezoid for your input V\n";
            cout << T;
            cout << "Or just copy this: 1.000000 2.000000 3.000000 2.000000 4.000000 0.000000 0.0000000 0.000000\n";
            cout << "Input dots: ";
            cin >> Tinput;

            cout << " V Rhombus for your input V\n";
            cout << R;
            cout << "Or just copy this: 987 321 139.605 562.272 -741 591 106.395 349.728\n";
            cout << "Input dots: ";
            cin >> Rinput;
        }

        FigureCollection FC;
        FC.pushBack(&Pinput);
        FC.pushBack(&Tinput);
        FC.pushBack(&Rinput);

        FC.displayGCenters();
        cout << "\n";
        FC.displayAreas();
        cout << "\n";
        cout << "SUM AREA = " << FC.getAllArea();
        cout << "\n";
        cout << FC;

    return 0;
}
