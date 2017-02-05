// -*-coding: mule-utf-8-unix; fill-column: 58 -*- *********
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

#ifndef _BITS_STREAM_ITERATOR_H_
#define _BITS_STREAM_ITERATOR_H_

#include <istream>
#include <ostream>
#include <bits/ext_constr.h>

namespace std {

// 24.6 Stream iterators

// 24.6.4 ostreambuf_iterator

template <class charT, class traits = char_traits<charT> >
class ostreambuf_iterator :
  public iterator<output_iterator_tag, void, void, void, void> {
public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef basic_streambuf<charT,traits> streambuf_type;
  typedef basic_ostream<charT,traits> ostream_type;

public:
  ostreambuf_iterator(ostream_type& s) noexcept
    : sbuf_(s.rdbuf())
  {
    //FIXME nullptr
  }

  ostreambuf_iterator(streambuf_type* s) noexcept
    : sbuf_(s)
  {
    //FIXME nullptr
  }

  ostreambuf_iterator& operator = (charT c) noexcept
  {
    if (!failed())
      failed_ = (sbuf_->sputc(c) == traits::eof());

    return *this;
  }

  ostreambuf_iterator& operator * ()
  {
    return *this;
  }

  ostreambuf_iterator& operator ++ ()
  {
    return *this;
  }
  
  ostreambuf_iterator& operator ++ (int)
  {
    return *this;
  }

  bool failed() const noexcept
  {
    return failed_;
  }

private:
  streambuf_type* sbuf_;
  bool failed_ = false;
};

namespace bits {

template<class CharT, class Traits>
struct dummy_streambuf_instance
{
  static _externally_constructed<
    dummy_streambuf<CharT, Traits>
  > instance;
};


#if 0
template<class CharT, class Traits>
_externally_constructed<dummy_streambuf<CharT, Traits>> dummy_streambuf_instance<CharT, Traits>
//
::instance {};
#endif

} // namespace bits

template <class CharT, class Traits = char_traits<CharT> >
class istreambuf_iterator :
  public iterator<
    input_iterator_tag,
    CharT,
    typename Traits::off_type,
    CharT*,
    CharT
  >
{
public:
  typedef CharT char_type;
  typedef Traits traits_type;
  typedef basic_streambuf<CharT,Traits> streambuf_type;
  typedef basic_istream<CharT,Traits> istream_type;

public:
  constexpr istreambuf_iterator() noexcept
    : sbuf_(&bits::dummy_streambuf_instance<CharT, Traits>::instance)
  {
  }

  istreambuf_iterator(istream_type& s) noexcept
    : sbuf_(s.rdbuf())
  {
    //FIXME nullptr
  }

  istreambuf_iterator(streambuf_type* s) noexcept
    : sbuf_(s)
  {
    //FIXME nullptr
  }

  char_type operator*() const noexcept
  {
    return sbuf_->sgetc();
  }

  istreambuf_iterator& operator++ ()
  {
    sbuf_->sbumpc();
    return *this;
  }
  
  istreambuf_iterator& operator++ (int)
  {
    sbuf_->sbumpc();
    return *this;
  }

  bool equal(const istreambuf_iterator& it) const noexcept
  {
    return (*(*this) == Traits::eof()) == (*it == Traits::eof());
  }

  bool operator==(const istreambuf_iterator& it) const noexcept
  {
    return equal(it);
  }
  
  bool operator!=(const istreambuf_iterator& it) const noexcept
  {
    return !equal(it);
  }
  
private:
  streambuf_type* sbuf_;
};



} // std

#endif

