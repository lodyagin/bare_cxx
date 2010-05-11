//===----------------------------------------------------------------------===//
//
// ΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚThe LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <iterator>

// class ostream_iterator

// ostream_iterator(ostream_type& s, const charT* delimiter);

#include <iterator>
#include <sstream>
#include <cassert>

int main()
{
    {
        std::ostringstream outf;
        std::ostream_iterator<int> i(outf, ", ");
        assert(outf.good());
    }
    {
        std::wostringstream outf;
        std::ostream_iterator<double, wchar_t> i(outf, L", ");
        assert(outf.good());
    }
}
