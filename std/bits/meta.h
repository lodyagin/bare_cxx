// -*-coding: mule-utf-8-unix; fill-column: 59 -*-
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++
 * library is a standard library specially designed for
 * systems without memory protection like exokernel
 * operating systems.
 *
 * Metaprogramming primitives.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2013 Cohors LLC
 *
 */

#ifndef _STD_BITS_META_H_
#define _STD_BITS_META_H_

#include <type_traits>

namespace std { namespace bits {

//! Check whether flag is true (it is typically a
//! metaprogramming predicate with a value member of a
//! type bool)
//!
//! template<class T>
//! auto fun(...) -> 
//! EnableFunIf(is_same<T, QString>::value, FunReturnType)&
template<bool flag, class RetType>
using EnableFunIf = typename std::remove_reference <
  decltype(typename std::enable_if<flag>::type(),
  std::declval<RetType>()) 
> :: type;

}}

#endif
