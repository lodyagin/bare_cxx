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

#ifndef _NUM_PUT_HPP
#define _NUM_PUT_HPP

#include <locale>
#include <array>
#include <bits/constexpr_math.h>

namespace std { namespace bits {

namespace {

template<class CharT>
struct Digits {};

template<>
struct Digits<char>
{
  constexpr static std::array<char, 16> digit =
    {{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
     'a', 'b', 'c', 'd', 'e', 'f'}};
};

}

template<class T, class CharT, class OutputIt>
OutputIt num_put
  ( OutputIt out, 
    ios_base& str, 
    CharT fill, 
    T v )
{
  constexpr size_t max_len = 
    digits<10, pow2x<sizeof(v) * 8 - 1>::value>::value + 1;

  unsigned base = 10; // FIXME

  std::array<CharT, max_len> buf;
  auto it = buf.end();
  auto num = v;
  while (num > 0) 
  {
    *--it = Digits<CharT>::digit[num % base];
    num /= base;
  }

  return std::copy(it, buf.end(), out);
}

}}

#endif
