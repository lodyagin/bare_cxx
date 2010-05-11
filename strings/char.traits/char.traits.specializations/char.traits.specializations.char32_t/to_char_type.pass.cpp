//===----------------------------------------------------------------------===//
//
// ΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚThe LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// template<> struct char_traits<char32_t>

// static constexpr char_type to_char_type(int_type c);

#include <string>
#include <cassert>

int main()
{
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    assert(std::char_traits<char32_t>::to_char_type(U'a') == U'a');
    assert(std::char_traits<char32_t>::to_char_type(U'A') == U'A');
    assert(std::char_traits<char32_t>::to_char_type(0) == 0);
#endif
}
