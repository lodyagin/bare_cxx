// -*-coding: mule-utf-8-unix; fill-column: 58 -*- ********
/** 
 * @file
 *
 * This file is a part of Bare C++ library. Bare C++
 * library is a standard library specially designed for
 * systems without memory protection like exokernel
 * operating systems.
 *
 * @author Sergei Lodyagin <serg@kogorta.dp.ua>
 * @copyright (C) 2014 Cohors LLC
 *
 */

#ifndef _BITS_LOCALE_H_
#define _BITS_LOCALE_H_

#include <cstddef>

namespace std {

class ios_base;

class locale
{
public:
  class facet
  {
  protected:
	 explicit facet(std::size_t refs = 0)
	 {
		// TODO facet auto-deletion
		// assert (refs != 0);
	 }

    facet(const facet&) = delete;
	 facet& operator = (const facet&) = delete;
	 virtual ~facet() {};
  };
};

} // std

#endif
