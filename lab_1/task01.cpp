#include <iostream>
#include "box_capacity.h"

int main()
{
  double feet_lenght;
  double feet_width;
  double feet_height;
  std::cout << "enter lenght in feet: ";
  std::cin  >> feet_lenght;
  std::cout << "enter width in feet: ";
  std::cin  >> feet_width;
  std::cout << "enter height in feet: ";
  std::cin  >> feet_height;

  unsigned int result = box_capacity(feet_lenght, feet_width, feet_height);


  std::cout << "result: " << result << std::endl;

  return 0;
}