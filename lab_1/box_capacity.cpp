#include "box_capacity.h"
#include <iostream>

double INCH_BOX_SIZE = 16;

double feet_in_inch(double num) {
    return num * 12;
}

unsigned int box_capacity(double feet_legth, double feet_width, double feet_height){
    if (feet_legth < 0 || feet_width < 0 || feet_height < 0) return 0;

    unsigned int x = (unsigned int) feet_in_inch(feet_legth) / INCH_BOX_SIZE;
    unsigned int y = (unsigned int) feet_in_inch(feet_width) / INCH_BOX_SIZE;
    unsigned int z = (unsigned int) feet_in_inch(feet_height) / INCH_BOX_SIZE;

    return x*y*z;
}