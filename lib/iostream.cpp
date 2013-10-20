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

namespace std {

// FIXME std::atomic, see http://stackoverflow.com/questions/10521263/standard-way-to-implement-initializer-like-ios-baseinit
static unsigned int nifty_counter;

ios_base::Init::Init()
{
  if (nifty_counter++ == 0)
  {
    new(&cout) ostream(new streambuf());
  }
}

ios_base::Init::~Init()
{
  if (--nifty_counter == 0)
  {
    cout.flush();
  }
}

}
