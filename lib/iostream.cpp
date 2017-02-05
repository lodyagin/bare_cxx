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

#include <new>
#include <string>
#include <streambuf>
#include <ostream>
#include <bits/ext_constr.h>
#include <bare/video>

namespace std {

using namespace bare;
using namespace bits;

_externally_constructed
  <video::basic_streambuf<char>>
    _terminal_io_streambuf_inst;

_externally_constructed<basic_ostream<char>> cout;
_externally_constructed<basic_ostream<char>> cerr;
_externally_constructed<basic_ostream<char>> clog;
_externally_constructed<basic_istream<char>> cin;

// Chec the compiler inserts a thread guard.
// Answer http://stackoverflow.com/questions/10521263/standard-way-to-implement-initializer-like-ios-baseinit

namespace {

unsigned int nifty_counter;

}

ios_base::Init::Init()
{
  if (nifty_counter++ == 0)
  {
    new(&_terminal_io_streambuf_inst.m) 
      video::basic_streambuf<char>();

    new(&cout.m) ostream
      (&_terminal_io_streambuf_inst.m);
    new(&cerr.m) ostream
      (&_terminal_io_streambuf_inst.m);
    new(&clog.m) ostream
      (&_terminal_io_streambuf_inst.m);
    new(&cin.m) istream
      (&_terminal_io_streambuf_inst.m);

    new(&bits::dummy_streambuf_instance<char, std::char_traits<char>>
         ::instance)
         bits::dummy_streambuf_instance<char, std::char_traits<char>>();
  }
}

ios_base::Init::~Init()
{
  if (--nifty_counter == 0)
  {
    cout.m.flush();
  }
}

} // namespace std
