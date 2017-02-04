#include <iostream>

#define LINUX
#include "std/bare/video"

constexpr unsigned long m = 10;

static char buf[m+1];

int main()
{
  std::cout << "Enter 10 chars please:" << std::endl;
  const long n = bare::b_input_chars(buf, m);
  buf[m] = 0;
  std::cout << "You entered " << n << " characters: [" << buf << "]"
    << std::endl;
}
