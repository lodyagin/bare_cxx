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

#ifndef _BITS_FACETS_H_
#define _BITS_FACETS_H_

#include <bits/stream_iterator.h>

namespace std {

namespace bits {

template<class T, class CharT, class OutputIt>
OutputIt num_put
  ( OutputIt out, 
    ios_base& str, 
    CharT fill, 
    T v );

}

template <
  class CharT,
  class OutputIt = ostreambuf_iterator<CharT>
>
class num_put : public locale::facet
{};

template<>
class num_put<char> : public locale::facet
{
public:
  typedef char char_type;
  typedef ostreambuf_iterator<char> iter_type;
  
  explicit num_put(size_t refs = 0)
	 : locale::facet(refs)
  {}

  iter_type put
	 ( iter_type out, 
      ios_base& str, 
      char_type fill, 
      unsigned long long v ) const
  {
	 return do_put(out, str, fill, v);
  }
	
//protected: // FIXME
  ~num_put() {}

protected:
  virtual iter_type do_put
	 ( iter_type out, 
      ios_base& str, 
      char_type fill, 
      unsigned long long v ) const
  {
    return bits::num_put(out, str, fill, v);
  }
};

} // std

#endif
