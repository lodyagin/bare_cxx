//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <chrono>

// typedef duration<signed integral type of at least 29 bits, ratio< 60>> minutes;

#include <chrono>
#include <type_traits>
#include <limits>

int main()
{
    typedef std::chrono::minutes D;
    typedef D::rep Rep;
    typedef D::period Period;
    static_assert(std::is_signed<Rep>::value, "");
    static_assert(std::is_integral<Rep>::value, "");
    static_assert(std::numeric_limits<Rep>::digits >= 28, "");
    static_assert((std::is_same<Period, std::ratio<60> >::value), "");
}
