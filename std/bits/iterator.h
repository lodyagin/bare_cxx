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

#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <type_traits>
#include <bits/meta.h>

namespace std { namespace bits {

template<class Iterator>
constexpr auto is_compatible(Iterator a, Iterator b)
  -> decltype(a.is_compatible(b), bool())
{
  return a.is_compatible(b);
}

template<class T>
constexpr bool is_compatible(T* a, T* b)
{
  return true;
}

// FIXME the case when no Iterator::is_compatible() exists

}}

#endif

