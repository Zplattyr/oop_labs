#include "closest_pair_tonum.h"

std::string closest_pair_tonum(int border){
    if(border <= 2) {
        return "Border is too low";
    }
    int squares[100];
    int num_of_squares{0};
    while(num_of_squares*num_of_squares <= (border-1)*2)
    {
        squares[num_of_squares] = num_of_squares*num_of_squares;
        ++num_of_squares;
    }
    int a = border - 1;
    while(a != 0)
    {
       for(int i = num_of_squares; i > 0; --i)
       {
        int b = squares[i] - a;
        if(b < a)
        {
            for(int k = i - 1; k > 0; --k)
            {
                if(a - b == squares[k]){
                    return "(" + std::to_string(a) + "," + std::to_string(b) + ")";
                }
            }
        }
       }
       --a;
    }
    return "Don't exist";
}