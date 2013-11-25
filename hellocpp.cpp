#include <iostream>
#include <locale>
#include <limits>
#include <bits/constexpr_math.h>

using namespace std;

class np : public num_put<char> 
{
public:
  np() : num_put(1) {}
};

int main()
{
  ostreambuf_iterator<char> out(cout);
  np n;

  cout << "Hello World!\n";
  cout << "I know different numbers.\n";

  cout << "Million:\t";
  n.put(out, cout, ' ', bits::pow10x<6>::value);
  cout << "\n";

  cout << "Billion:\t";
  n.put(out, cout, ' ', bits::pow10x<9>::value);
  cout << "\n";

  cout << "Trillion:\t";
  n.put(out, cout, ' ', bits::pow10x<12>::value);
  cout << "\n";

  cout << "Quadrillion:\t";
  n.put(out, cout, ' ', bits::pow10x<15>::value);
  cout << "\n";

  cout << "Quintillion:\t";
  n.put(out, cout, ' ', bits::pow10x<18>::value);
  cout << "\n";

  cout << "My biggest number is:\t";
  n.put(out, cout, ' ', numeric_limits<uintmax_t>::max());
  cout << "\n";

  cout << "Bye!\n";
}
