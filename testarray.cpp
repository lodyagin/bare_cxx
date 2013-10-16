#define _STD bare
#include <iostream>
#include "std/array"

using namespace _STD;

using A = array<int, 100>;

void out(A& a) 
{
  for (A::iterator it = a.begin(); it != a.end(); it++)
    std::cout << *it;
}

int main(int argc, char* argv[])
{
  A a;
  int n1, n2;
  std::cin >> n1 >> n2;

#if 0
  int i = 1;
  for (auto& v : a) 
    v = i++;
#else
  A::iterator i1 = a.begin() + n1;
  ++i1;
  *i1 = 135;
  A::iterator i2 = i1 + n2;
  *i2 = 136;
#endif
  out(a);
}
