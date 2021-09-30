// Dumps io ports contents

#include <bare/ioport>
#include <iostream>
#include <ios>

using namespace std;
using namespace bare::ioport;

int main()
{
	using input_range = input::range<0, 32, std::uint8_t>;

	for (auto el : input_range{}) {
		cout std::hex << (int) 0/**el*/ << ' ';
	}
	cout << std::endl;
}
