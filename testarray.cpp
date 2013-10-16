#define _STD bare
#include <iostream>
#include "std/array"

using namespace _STD;

using A = array<int, 10>;

void out(array<int, 10>& a) 
{
  for (A::iterator it = a.begin(); it != a.end(); it++)
    std::cout << *it;
}

int main(int argc, char* argv[])
{
  A a;
  int n1, n2;

#if 1
  int i = 1;
  for (auto& v : a) 
    v = i++;
#endif
/*
  A::iterator i1 = a.begin() + n1;
  ++i1;
  *i1 = 135;
  A::iterator i2 = i1 + n2;
  *i2 = 136;
  */
  out(a);
}
