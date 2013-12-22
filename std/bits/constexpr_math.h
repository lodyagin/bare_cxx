// -*-coding: mule-utf-8-unix; fill-column: 59 -*-
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

#ifndef _STD_BITS_CONSTEXPR_MATH_H
#define _STD_BITS_CONSTEXPR_MATH_H

#include <cstdint>

namespace std {  namespace bits {

// FIXME add overflow
template<uintmax_t x>
struct log2x 
{
  enum : uintmax_t{ value = log2x<(x >> 1)>::value + 1 };
};

template<> 
struct log2x<1>
{
  enum { value = 0 };
};

// FIXME add overflow
// value is number of radix digits in x
template<unsigned radix, uintmax_t x>
struct digits
{
  enum : uintmax_t{ value = digits<radix, x / radix>::value + 1 };
};

template<unsigned radix> 
struct digits<radix, 0> { enum { value = 0}; };

template<uint8_t x>
struct pow2x
{
  enum : uintmax_t { value = 2 * pow2x<x - 1>::value };
};

template<>
struct pow2x<0>
{
  enum : uintmax_t { value = 1 };
};

template<uint8_t x>
struct pow10x
{
  enum : uintmax_t { value = 10 * pow10x<x - 1>::value };
};

template<>
struct pow10x<0>
{
  enum : uintmax_t { value = 1 };
};

//! Return mask with n lower bits set
template<uint8_t n, class T = uint8_t>
constexpr T n_bits_mask()
{
  return pow2x<n+1>::value - 1;
}

}
}

#endif



