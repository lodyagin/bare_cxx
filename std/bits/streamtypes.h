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

#ifndef _STD_BITS_STREAMTYPES_H
#define _STD_BITS_STREAMTYPES_H

#include <cwchar>

namespace std {

typedef intmax_t streamoff;
typedef intmax_t streamsize;

template<class State>
class fpos
{
//TODO
};


typedef fpos<mbstate_t> streampos;

}

#endif

