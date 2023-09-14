#include <iostream>
#include "closest_pair_tonum.h"

int main()
{
  int border;
  std::cout << "enter border: ";
  std::cin  >> border;

  std::string result = closest_pair_tonum(border);


  std::cout << "result: " << result << std::endl;

  return 0;
}