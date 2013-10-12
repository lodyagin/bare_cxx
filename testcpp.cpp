#include "bare_memory.hpp"

using namespace bare;

int main(int argc, char* argv[]) noexcept
{
  const int max_n = 100000;
  bitmap<max_n> b; // = {0};

  for(auto bit : b)
    bit = 1;

}
