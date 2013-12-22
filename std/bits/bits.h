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

#ifndef _BITS_BITS_
#define _BITS_BITS_

#include "bits/constexpr_math.h"

namespace std { namespace bits {

template<class Int>
void rol(Int& i, uint8_t shift)
{
  assert(shift & n_bits_mask<log2x<sizeof(Int)*8>::value>()
         == shift);

  asm ("rol %0, cl"
       : "+rm" (i)
       : "Jc" (shift));
}

template<class Int>
void ror(Int& i, uint8_t shift)
{
  assert(shift & n_bits_mask<log2x<sizeof(Int)*8>::value>()
         == shift);

  asm ("ror %0, cl"
       : "+rm" (i)
       : "Jc" (shift));
}

}}

#endif


