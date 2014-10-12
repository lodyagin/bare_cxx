// -*-coding: mule-utf-8-unix; fill-column: 58 -*- ********
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++
 * library is a standard library specially designed for
 * systems without memory protection like exokernel
 * operating systems.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2014 Cohors LLC
 *
 */

#include <ostream>
#include <utility>
#include <bits/stream_iterator.h>
#include "types/compound_message.h"

#ifndef _BITS_LOWLEVEL_OUTPUT_H_
#define _BITS_LOWLEVEL_OUTPUT_H_

namespace std { 
namespace bits {

template<class... Args>
void out_message(std::ostream& out, Args&&... args) noexcept
{
  using Out = std::ostreambuf_iterator<char>;
  types::compound_message<Out>(std::forward<Args>(args)...)
    . stringify(Out(out.rdbuf()), out);
}

} // bits
} // std

#endif
