// -*-coding: mule-utf-8-unix; fill-column: 58 -*-
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++
 * library is a standard library specially designed for
 * systems without memory protection like exokernel
 * operating systems.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2013 Cohors LLC
 *
 */

#include <bits/facets.h>
#include "./num_put.hpp"

namespace std { namespace bits {

constexpr std::array<char, 16> Digits<char>::digit;

template
std::ostreambuf_iterator<char> num_put
  ( std::ostreambuf_iterator<char> out, 
    std::ios_base& str, 
    char fill, 
    unsigned long long v );

}}


