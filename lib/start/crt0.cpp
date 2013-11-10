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

#include <algorithm>
#include <string>
#include <initializer_list>
#include <cstdlib>
#include <csetjmp>

inline unsigned long b_system_config_crt0
  (unsigned long function, unsigned long var)
{
  unsigned long tlong;
  asm volatile 
    ("call *0x001000B0" 
     : "=a"(tlong) 
     : "d"(function), "a"(var));
  return tlong;
}

extern int main
  (/*std::initializer_list<bare::constexpr_string>*/);

namespace {

inline void zero_bss()
{
  extern char __bss_start, _end;
  std::fill(&__bss_start, &_end, 0);
}

}

// set by std::exit(int) family
int _exit_code;

std::jmp_buf _exit_jump_buf;

extern "C" void _init(); 

extern "C" int _start()
{
  zero_bss();
  _init();

  if (setjmp(_exit_jump_buf))
    return _exit_code; // longjmp was made
  else 
    // FIXME change to std::exit
    std::_Exit(main()); // noreturn, will allways long jump
}

