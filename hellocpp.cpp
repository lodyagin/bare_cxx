#include <iostream>
#include <locale>
#include <limits>
#include <bits/constexpr_math.h>
#include <bitset>

using namespace std;

class np : public num_put<char> 
{
public:
  np() : num_put(1) {}
};

int main()
{
  // bitset<10> a("0101");

  ostreambuf_iterator<char> out(cout);
  np n;

  cout << "Hello World!\n";
  cout << "I know different numbers.\n";

  cout << "Million:\t" << std::bits::pow10x<6>::value << '\n';
  cout << "Billion:\t" << std::bits::pow10x<9>::value << '\n';
  cout << "Trillion:\t" << std::bits::pow10x<12>::value << '\n';
  cout << "Quadrillion:\t" << std::bits::pow10x<15>::value << '\n';
  cout << "Quintillion:\t" << std::bits::pow10x<18>::value << '\n';
  cout << "My biggest number is:\t"
       << numeric_limits<uintmax_t>::max() << '\n';
  cout << "Bye!\n";
}
