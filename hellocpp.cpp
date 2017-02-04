#include <iostream>
#include <locale>
#include <limits>
#include <bits/constexpr_math.h>
#include <bitset>
#include <types/string.h>

using namespace std;
using namespace strings;

int main()
{
  auto_string<5> name;

  cout << "Hello World!\n";
  cout << "By the way, what is your name?\n";
  cin >> name;
  cout << "Hello " << name << "!\n";
  if (name.overflow())
    cout << "(sorry, I can remember only " << name.buf_size() - 1 << " last characters of your name)\n";
  cout << "\nI know different numbers.\n";

  cout << "Million:\t" << std::bits::pow10x<6>::value << '\n';
  cout << "Billion:\t" << std::bits::pow10x<9>::value << '\n';
  cout << "Trillion:\t" << std::bits::pow10x<12>::value << '\n';
  cout << "Quadrillion:\t" << std::bits::pow10x<15>::value << '\n';
  cout << "Quintillion:\t" << std::bits::pow10x<18>::value << '\n';
  cout << "My biggest number is:\t"
       << numeric_limits<uintmax_t>::max() << '\n';

#if 0       
  uintmax_t yourth;
  cout << "\nWhat is your biggest number? Please enter it here: ";
  cin >> yourth;
  cout << "I can read it as " << yourth << '\n';
#endif

  cout << "Bye!\n";
}
