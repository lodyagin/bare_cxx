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

#include <iostream>
#include <cstdlib>

extern "C" void __cxa_pure_virtual()
{
  std::cerr << 
    strings::fast_constant(
      "<bare_c++lib>: a pure virtual function called.\n"
    );
  std::abort();
}
