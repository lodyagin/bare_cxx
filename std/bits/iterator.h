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

#ifndef _BITS_ITERATOR_H_
#define _BITS_ITERATOR_H_

#include <type_traits>

namespace std { 
namespace bits {

template<class Iterator>
constexpr auto is_compatible(Iterator a, Iterator b)
  -> decltype(a.is_compatible(b), bool())
{
  return a.is_compatible(b);
}

template<class T>
constexpr bool is_compatible(T* a, T* b)
{
  return true;
}

// FIXME the case when no Iterator::is_compatible() exists

} // bits

// iterator categories

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag 
  : public input_iterator_tag {};

struct bidirectional_iterator_tag 
  : public forward_iterator_tag {};

struct random_access_iterator_tag 
  : public bidirectional_iterator_tag {};

// the iterator base class

template <
  class Category,
  class T,
  class Distance = std::ptrdiff_t,
  class Pointer = T*,
  class Reference = T&
> 
struct iterator
{
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template<class Iterator>
struct iterator_traits
{
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

// 24.5 Iterator adaptors

// 24.5.1 Reverse iterators

template<class Iterator>
class reverse_iterator 
  : public iterator <
      typename iterator_traits<Iterator>::iterator_category,
      typename iterator_traits<Iterator>::value_type,
      typename iterator_traits<Iterator>::difference_type,
      typename iterator_traits<Iterator>::pointer,
      typename iterator_traits<Iterator>::reference 
    >
{
  typedef iterator_traits<Iterator> TR;
public:
  typedef Iterator iterator_type;
  typedef typename TR::difference_type difference_type;
  typedef typename TR::pointer pointer;
  typedef typename TR::reference reference;

  explicit reverse_iterator(Iterator x) : current(x) 
  {}

  template<class U>
  reverse_iterator(const reverse_iterator<U>& other)
    : current(other.base())
  {}

  template<class U>
  reverse_iterator& operator = 
    (const reverse_iterator<U>& other)
  {
    current = other.base();
  }

  Iterator base() const
  {
    return current;
  }

  reference operator * () const
  {
    Iterator copy(current);
    return *--copy;
  }

  pointer operator -> () const
  {
    return &(operator*());
  }

  reverse_iterator& operator ++ ()
  {
    --current;
    return *this;
  }

  reverse_iterator operator ++ (int) &
  {
    reverse_iterator copy(*this);
    ++(*this);
    return copy;
  }

  reverse_iterator operator ++ (int) &&
  {
    return *this;
  }

  reverse_iterator& operator += (difference_type n)
  {
    current -= n;
    return *this;
  }

  reverse_iterator operator + (difference_type n) const &
  {
    return reverse_iterator(current - n);
  }

  reverse_iterator operator + (difference_type n) &&
  {
    current -= n;
    return *this;
  }

  reverse_iterator& operator -- ()
  {
    ++current;
    return *this;
  }

  reverse_iterator operator -- (int) &
  {
    reverse_iterator copy(*this);
    --(*this);
    return copy;
  }

  reverse_iterator operator -- (int) &&
  {
    return *this;
  }

  reverse_iterator& operator -= (difference_type n)
  {
    current += n;
    return *this;
  }

  reverse_iterator operator - (difference_type n) const &
  {
    return reverse_iterator(current + n);
  }

  reverse_iterator operator - (difference_type n) &&
  {
    current += n;
    return *this;
  }

  reference operator [] (difference_type n) const
  {
    return current.operator[](-n-1);
  }

  constexpr bool is_compatible(reverse_iterator b)
  {
    return bits::is_compatible(current, b.current);
  }

protected:
  Iterator current;
};

template<class I1, class I2>
bool operator == 
  ( const reverse_iterator<I1>& lhs, 
    const reverse_iterator<I2>& rhs)
{
  return lhs.base() == rhs.base();
}

template<class I1, class I2>
bool operator != 
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
{
  return lhs.base() != rhs.base();
}

template<class I1, class I2>
bool operator <
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
{
  return lhs.base() > rhs.base();
}

template<class I1, class I2>
bool operator <=
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
{
  return lhs.base() >= rhs.base();
}

template<class I1, class I2>
bool operator >
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
{
  return lhs.base() < rhs.base();
}

template<class I1, class I2>
bool operator >=
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
{
  return lhs.base() <= rhs.base();
}

template<class I>
reverse_iterator<I> operator +
  (typename reverse_iterator<I>::difference_type n,
   const reverse_iterator<I>& it)
{
  return reverse_iterator<I>(it.base() - n);
}

template<class I1, class I2>
auto operator -
  (const reverse_iterator<I1>& lhs, const reverse_iterator<I2>& rhs)
  -> decltype(rhs.base() - lhs.base())
{
  return rhs.base() - lhs.base();
}

} // std

#endif

