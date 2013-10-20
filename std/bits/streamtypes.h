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

#ifndef _STREAMTYPES_H_
#define _STREAMTYPES_H_

#include <cwchar>

namespace std {

typedef intmax_t streamoff;

template<class State>
class fpos
{
//TODO
};


typedef fpos<mbstate_t> streampos;

}

#endif

