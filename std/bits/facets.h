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

#ifndef _STD_LOCALES
class ctype_base
{
public:
  typedef uint16_t mask;

  static constexpr mask space = 0x0001;
};

template<class CharT>
class ctype;

template<>
class ctype<char> : public ctype_base, public locale::facet
{
public:
  typedef char char_type;

  explicit ctype(std::size_t refs = 0) noexcept
  {
    tab[32] = tab['\f'] = tab['\n'] = tab['\r'] = tab['\t'] = tab['\v'] = space;
  }

  bool is(mask m, char c) const noexcept
  {
    return tab[c] & m;
  }
  
//protected: // FIXME
  ~ctype() {}

protected:
  array<mask, 256> tab = {};
};
  
namespace bits {

template<class T, class CharT, class OutputIt>
OutputIt num_put
  ( OutputIt out, 
    ios_base& str, 
    CharT fill, 
    T v );
  
} // namespace bits

template <
  class CharT,
  class OutputIt = ostreambuf_iterator<CharT>
>
class num_put : public locale::facet
{};
  
template <
  class CharT,
  class InputIt = istreambuf_iterator<CharT>
>
class num_get : public locale::facet
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
  
namespace bits
{

//! Usually most of them must come from the locale but 
//! keeping them separately gives more freedom
//! like using different OutputIt types
//! (e.g. output directly to a char buffer).
struct facets
{
#if 0 // TODO - static in function
    template<class Facet>
    static const Facet& locale_independent()
    {
        static Facet* f = new Facet(1); /* NB ref count is 1 */ 
        assert(f);
        return *f;
    }
#else

  struct locale_independent
  {
    template<class CharT, class OutputIt>
    struct num_put
    {
          static ::std::num_put<CharT, OutputIt> facet;
    };

    template<class CharT>
    struct ctype
    {
          static ::std::ctype<CharT> facet;
    };
  };
#endif
};

#if 0
template<class CharT, class OutputIt>
::std::num_put<CharT, OutputIt> facets::
locale_independent::num_put<CharT, OutputIt>
//
::facet {};
#endif
 
} // namespace bits

#endif // _STD_LOCALES
} // std

#endif
