// -*-coding: mule-utf-8-unix; fill-column: 58 -*-
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++ library is a standard
 * library specially designed for systems without memory protection like
 * exokernel operating systems.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2013 Cohors LLC
 *
 */

#include <cstdlib>
#include <csetjmp>

namespace std {

namespace bits {
  extern jmp_buf _exit_jump_buf;
  extern int _exit_code;
}

[[noreturn]] void abort() noexcept
{
  _Exit(EXIT_FAILURE);
}

[[noreturn]] void exit(int exit_code);

[[noreturn]] void _Exit(int exit_code) noexcept
{
  bits::_exit_code = exit_code;
  longjmp(bits::_exit_jump_buf, 1);
}

}


