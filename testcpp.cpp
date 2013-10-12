#include "bare_memory.hpp"
#include <iostream>

using namespace bare;
using namespace std;

int main(int argc, char* argv[])
{
  int i;
  ++i = 1;
  i++ = 1;
  

  bitmap<8> b8;

  bitmap<8>::iterator it = b8.begin();
  for (int i = 0; i < 7; i++)
    *++it = i % 2;

  it = b8.begin();
  for (int i = 0; i < 7; i++)
    cout << *++it;
  cout << endl;
  return 0;
}
