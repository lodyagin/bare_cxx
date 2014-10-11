// -*-coding: mule-utf-8-unix; fill-column: 59 -*- *******
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
#include "unwind.h"
#include <bare/video>

//! Debug output
#define DBG_(msg) \
  bare::video::basic_streambuf<char>().sputn(msg)

#define ABORT_DBG_(msg) \
  DBG_(msg), std::abort()

#define DBG(msg)                               \
  static_assert(                               \
    noexcept(DBG_(msg)),                       \
   "Need to use some noexcept output command"  \
  );                                           \
  DBG_(msg);                      

#define ABORT_DBG(msg)                         \
  static_assert(                               \
    noexcept(ABORT_DBG_(msg)),                 \
   "Need to use some noexcept output command"  \
  );                                           \
  ABORT_DBG_(msg);                      

[[noreturn]] void _Unwind_Resume(
  _Unwind_Exception* exception_object
) noexcept
{
  ABORT_DBG("_Unwind_Resume()\n");
}

_Unwind_Reason_Code __gxx_personality_v0(
  int version,
  _Unwind_Action actions,
  std::uint64_t exceptionClass,
  _Unwind_Exception* exceptionObject,
  _Unwind_Context* context
) noexcept
{
  DBG("__gxx_personality_v0()\n");
  return _URC_CONTINUE_UNWIND;
}
