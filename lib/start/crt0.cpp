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

#define LINUX_CROSS

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

int main(/*std::initializer_list<bare::constexpr_string>*/);

extern char __bss_start, _end;

typedef void (*ctor_t)();

extern "C" ctor_t __init_array_start[];
extern "C" ctor_t __init_array_end[];

namespace {

inline void zero_bss()
{
  std::fill(&__bss_start, &_end, 0);
}

}

namespace std {

// set by std::exit(int) family
int _exit_code;

jmp_buf _exit_jump_buf;

}

extern "C" void _init(); 
extern "C" void _fini(); 

#ifndef LINUX_CROSS
extern "C" int _start()
#else
extern "C" void _start()
#endif
{
  using namespace std;

  zero_bss();
  _init();

  for_each(__init_array_start, __init_array_end,
           [](ctor_t ctor) 
           {
              (*ctor)(); 
           });

  if (!setjmp(_exit_jump_buf))
    // FIXME change to std::exit
    std::_Exit(main()); // noreturn, will allways long jump

  _fini();
#ifndef LINUX_CROSS
  return _exit_code; // longjmp was made
#else
  asm ("mov $1, %rax\n\t"
       "xor %ebx, %ebx\n\t"
       "int $0x80");
#endif
}

