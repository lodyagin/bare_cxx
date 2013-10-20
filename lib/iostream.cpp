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


/**
  * Output to a terminal.
  * @author Sergei Lodyagin
  */
template <
  class CharT,
  class Traits = std::char_traits<CharT>
>
class _terminal_out_streambuf 
  : public basic_streambuf<CharT, Traits>
{
protected:
  streamsize xsputn
    (const char_type* s, std::streamsize count) override
  {
    b_output_chars(s, count);
    return count;
  }
};


// FIXME std::atomic, see http://stackoverflow.com/questions/10521263/standard-way-to-implement-initializer-like-ios-baseinit
static unsigned int nifty_counter;

ios_base::Init::Init()
{
  if (nifty_counter++ == 0)
  {
    new(&cout) ostream(new _terminal_out_streambuf());
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
