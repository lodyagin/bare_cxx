#include "std/cstdlib"
#include <iostream>

using namespace std;

volatile int _x;
volatile int _y;

void test(int x, int y)
{
  const bare_div_t d = bare_div(x, y);
#if 1
  cout << d.quot << '|' << d.rem << " == "
       << x/y << '|' << x%y
       << endl;
#else
  _x = d.quot;
  _y = d.rem;
#endif
}

void test2(int x, int y)
{
#if 0
  bare_div_t d;
  d.quot = x/y;
  d.rem = x % y;
  cout << d.quot << '|' << d.rem << " == "
       << endl;
#else
  _x = x/y;
  _y = x % y;
#endif
}

int main(int argc, char* argv[])
{
  test(384, 10);
  test(-384, 10);
  test(384, -10);
  test(-384, -10);
  test(42, -5);
  test(-42, 5);
}
