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

#include <new>
#include <string>
#include <streambuf>
#include <ostream>

namespace bare {

inline void b_output_chars(const char *str, unsigned long nbr)
{
	asm volatile ("call *0x00100018" : : "S"(str), "c"(nbr));
}

}

namespace std {

using namespace bare;

/**
  * Output to a terminal.
  * @author Sergei Lodyagin
  */
template <
  class CharT,
  class Traits = std::char_traits<CharT>
>
class _terminal_out_basic_streambuf 
  : public basic_streambuf<CharT, Traits>
{
  typedef typename 
    basic_streambuf<CharT, Traits>::char_type 
    char_type;

protected:
  streamsize xsputn
    (const char_type* s, std::streamsize count) override
  {
    b_output_chars(s, count);
    return count;
  }
};

// T is a type to be constructed externally by a placement
// new operator
template<class T>
union _externally_constructed
{
  _externally_constructed() {} // it is
  ~_externally_constructed() {} // never
  T m;
};

_externally_constructed
  <_terminal_out_basic_streambuf<char>>
    _terminal_out_streambuf_inst;

_externally_constructed<basic_ostream<char>> cout;
_externally_constructed<basic_ostream<char>> cerr;
_externally_constructed<basic_ostream<char>> clog;

// FIXME std::atomic, see http://stackoverflow.com/questions/10521263/standard-way-to-implement-initializer-like-ios-baseinit
static unsigned int nifty_counter;

ios_base::Init::Init()
{
  if (nifty_counter++ == 0)
  {
    new(&_terminal_out_streambuf_inst.m) 
      _terminal_out_basic_streambuf<char>();

    new(&cout.m) ostream
      (&_terminal_out_streambuf_inst.m);
    new(&cerr.m) ostream
      (&_terminal_out_streambuf_inst.m);
    new(&clog.m) ostream
      (&_terminal_out_streambuf_inst.m);
  }
}

ios_base::Init::~Init()
{
  if (--nifty_counter == 0)
  {
    cout.m.flush();
  }
}

}
