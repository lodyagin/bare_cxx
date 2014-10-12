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
#include <bits/stream_iterator.h>
#include <types/compound_message.h>

//! Debug output
#define DBG_(msg) \
  bare::video::basic_streambuf<char>().sputn(msg),    \
  bare::video::basic_streambuf<char>().sputn("\n")

#define ABORT_DBG_(msg) \
  DBG_(msg), std::abort()

#define DBG(msg)                               \
  static_assert(                               \
    noexcept(DBG_(msg)),                       \
   "Need to use some noexcept output command"  \
  );                                           \
  do { DBG_(msg); } while(false)

#define ABORT_DBG(msg)                         \
  static_assert(                               \
    noexcept(ABORT_DBG_(msg)),                 \
   "Need to use some noexcept output command"  \
  );                                           \
  do { ABORT_DBG_(msg); } while(false)

[[noreturn]] void _Unwind_Resume(
  _Unwind_Exception* exception_object
) noexcept
{
  ABORT_DBG("_Unwind_Resume()");
}

_Unwind_Reason_Code __gxx_personality_v0(
  int version,
  _Unwind_Action actions,
  std::uint64_t exceptionClass,
  _Unwind_Exception* exceptionObject,
  _Unwind_Context* context
) noexcept
{
  DBG("__gxx_personality_v0()");
  return _URC_CONTINUE_UNWIND;
}

void *__cxa_allocate_exception(std::size_t thrown_size)
{
  using Out = std::ostreambuf_iterator<char>;

  types::compound_message<Out>(
    "__cxa_allocate_exception(", thrown_size,
    ")\n"
  ).stringify(Out(std::cerr.rdbuf()), std::cerr);

  // FIXME no reenterant
  static char buf[255];

  if (thrown_size > sizeof(buf)) {
#if 1
    types::compound_message<Out>(
      "__cxa_allocate_exception(", thrown_size,
      ") out of memory"
    ).stringify(Out(std::cerr.rdbuf()), std::cerr);
    std::abort();
#else
    ABORT_DBG("__cxa_allocate_exception out of memory");
#endif
  }

  return buf;
}

void __cxa_throw(
  void *thrown_exception, 
  std::type_info *tinfo, 
  void (*dest) (void *) 
)
{
  // TODO dump exception
  ABORT_DBG("__cxa_throw()");
}
