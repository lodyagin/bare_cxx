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

#ifndef _BITS_SILENT_ASSERT_H_
#define _BITS_SILENT_ASSERT_H_

#include <cstdlib>

#ifdef NDEBUG
#define _silent_assert(cond) ((void)0)
#else
#define _silent_assert(cond) \
  do { \
    if (!(cond)) { \
		std::abort();								  \
    } \
  } while(0)
#endif

#endif



