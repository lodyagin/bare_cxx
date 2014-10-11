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

#include <cstdint>

#ifndef _UNWIND_H_
#define _UNWIND_H_

enum _Unwind_Reason_Code 
{
	_URC_NO_REASON = 0,
	_URC_FOREIGN_EXCEPTION_CAUGHT = 1,
	_URC_FATAL_PHASE2_ERROR = 2,
	_URC_FATAL_PHASE1_ERROR = 3,
	_URC_NORMAL_STOP = 4,
	_URC_END_OF_STACK = 5,
	_URC_HANDLER_FOUND = 6,
	_URC_INSTALL_CONTEXT = 7,
	_URC_CONTINUE_UNWIND = 8
};

typedef int _Unwind_Action;
constexpr _Unwind_Action _UA_SEARCH_PHASE = 1;
constexpr _Unwind_Action _UA_CLEANUP_PHASE = 2;
constexpr _Unwind_Action _UA_HANDLER_FRAME = 4;
constexpr _Unwind_Action _UA_FORCE_UNWIND = 8;


struct _Unwind_Exception;

typedef void (*_Unwind_Exception_Cleanup_Fn)(
  _Unwind_Reason_Code reason,
  _Unwind_Exception *exc
);

struct alignas(4) _Unwind_Exception 
{
  std::uint64_t exception_class;
  _Unwind_Exception_Cleanup_Fn exception_cleanup;
  std::uint64_t private_1;
  std::uint64_t private_2;
};

struct _Unwind_Context;

extern "C" {

[[noreturn]] void _Unwind_Resume(
  _Unwind_Exception* exception_object
) noexcept;

_Unwind_Reason_Code __gxx_personality_v0(
  int version,
  _Unwind_Action actions,
  std::uint64_t exceptionClass,
  _Unwind_Exception* exceptionObject,
  _Unwind_Context* context
) noexcept;

void *__cxa_allocate_exception(std::size_t thrown_size);

void __cxa_throw(
  void *thrown_exception, 
  std::type_info *tinfo, 
  void (*dest) (void *) 
);

}

// see http://monoinfinito.wordpress.com/2013/06/13/c-exceptions-under-the-hood-appendix-ii-metaclasses-and-rtti-on-c/
namespace __cxxabiv1 {
  struct __class_type_info {
    virtual void foo() {}
  } ti;

  struct __vmi_class_type_info {
    virtual void foo() {}
  } vmi_ti;
}

#endif


