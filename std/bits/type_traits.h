#ifndef _STD_BITS_TYPE_TRAITS_H
#define _STD_BITS_TYPE_TRAITS_H

#include <bits/libcxx/type_traits>

namespace std {

#if 0
// integral_constant<T,v>

template<class T, T v>
struct integral_constant
{
  typedef T value_type;
  typedef integral_constant type;

  static constexpr T value = v;

  constexpr operator value_type() const { return value; }
  constexpr value_type operator()() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// remove_reference

template<class T> 
struct remove_reference { typedef T type; };

template<class T> 
struct remove_reference<T&> { typedef T type; };

template<class T> 
struct remove_reference<T&&> { typedef T type; };

template<class T>
using remove_reference_t = 
  typename remove_reference<T>::type;

template<class T> 
struct remove_const { typedef T type; };

template<class T> 
struct remove_const<const T> { typedef T type; };
 
template<class T> struct remove_volatile
{ typedef T type; };

template<class T> 
struct remove_volatile<volatile T> { typedef T type; };

template<class T>
struct remove_cv 
{
  typedef typename remove_volatile
    <typename std::remove_const<T>::type>::type type;
};
 
// is_same<A, B>

template<class A, class B>
struct is_same : false_type {};

template<class A>
struct is_same<A,A> : true_type {};

// is_integral<T>

template<class T>
struct is_integral : false_type {};

template<>
struct is_integral<bool> : true_type {};

template<>
struct is_integral<char> : true_type {};

template<>
struct is_integral<signed char> : true_type {};

template<>
struct is_integral<unsigned char> : true_type {};

template<>
struct is_integral<char16_t> : true_type {};

template<>
struct is_integral<char32_t> : true_type {};

template<>
struct is_integral<wchar_t> : true_type {};

template<>
struct is_integral<short> : true_type {};

template<>
struct is_integral<unsigned short> : true_type {};

template<>
struct is_integral<int> : true_type {};

template<>
struct is_integral<unsigned int> : true_type {};

template<>
struct is_integral<long> : true_type {};

template<>
struct is_integral<unsigned long> : true_type {};

template<>
struct is_integral<long long> : true_type {};

template<>
struct is_integral<unsigned long long> : true_type {};

// is_floating_point<T>

template<class T>
struct is_floating_point : false_type {};

template<>
struct is_floating_point<float> : true_type {};

template<>
struct is_floating_point<double> : true_type {};

template<>
struct is_floating_point<long double> : true_type {};

// is_arithmetic<T>

template<class T>
struct is_arithmetic : integral_constant <
  bool,
  is_integral<T>::value || is_floating_point<T>::value
> 
{};

// is_void

template<class T>
struct is_void : false_type {};

template<>
struct is_void<void> : true_type {};

// is_fundamental

template<class T>
struct is_fundamental : integral_constant <
  bool,
  is_arithmetic<T>::value ||
  is_void<T>::value  ||
  is_same<nullptr_t, typename remove_cv<T>::type>::value
> 
{};

// is_enum

template<class T>
struct is_enum : integral_constant<bool, __is_enum(T)> {};

// is_pointer

template<class T>
struct is_pointer : false_type {};

template<class T>
struct is_pointer<T*> : true_type {};

// is_member_pointer

namespace bits {

template<class T>
struct is_member_pointer_helper : std::false_type {};
 
template<class T, class U>
struct is_member_pointer_helper<T U::*> : true_type {};
 
}

template<class T>
struct is_member_pointer : bits::is_member_pointer_helper
  <typename remove_cv<T>::type> 
{};

// is_scalar

template<class T>
struct is_scalar : integral_constant <
  bool,
  is_arithmetic<T>::value     ||
  is_enum<T>::value           ||
  is_pointer<T>::value        ||
  is_member_pointer<T>::value ||
  is_same<nullptr_t, typename remove_cv<T>::type>::value
> 
{};

// is_array

template<class T>
struct is_array : false_type {};
 
template<class T>
struct is_array<T[]> : true_type {};
 
template<class T, size_t N>
struct is_array<T[N]> : true_type {};

// is_union

template<class T>
struct is_union : integral_constant<bool, __is_union(T)> 
{};

// is_class

template<class T>
struct is_class : integral_constant<bool, __is_class(T)> 
{};

// is_object

template<class T>
struct is_object : integral_constant <
  bool,
  is_scalar<T>::value ||
  is_array<T>::value  ||
  is_union<T>::value  ||
  is_class<T>::value
> 
{};

// primary template
template<class>
struct is_function : false_type { };
 
// specialization for regular functions
template<class Ret, class... Args>
struct is_function<Ret(Args...)> : true_type {};
 
// specialization for variadic functions such as printf
template<class Ret, class... Args>
struct is_function<Ret(Args......)> : true_type {};

#if 0 // defined in libcxx
// add_rvalue_reference

template <
  class T,
  bool = is_object<T>::value || is_function<T>::value
>
struct add_rvalue_reference
{
  typedef T&& type;
};

template<class T>
struct add_rvalue_reference<T, false>
{
  typedef T type;
};

template<class T>
typename add_rvalue_reference<T>::type declval();
#endif

template<class T>
struct remove_all_extents { typedef T type;};
 
template<class T>
struct remove_all_extents<T[]> {
    typedef typename remove_all_extents<T>::type type;
};
 
template<class T, std::size_t N>
struct remove_all_extents<T[N]> {
    typedef typename remove_all_extents<T>::type type;
};
#endif

// Helper which adds a reference to a type when given a reference_wrapper
template<typename _Tp>
struct __strip_reference_wrapper
{
    typedef _Tp __type;
};

template<typename _Tp>
struct __strip_reference_wrapper<reference_wrapper<_Tp> >
{
    typedef _Tp& __type;
};

template<typename _Tp>
struct __strip_reference_wrapper<const reference_wrapper<_Tp> >
{
    typedef _Tp& __type;
};

template<typename _Tp>
struct __decay_and_strip
{
    typedef typename __strip_reference_wrapper<
     typename decay<_Tp>::type>::__type __type;
};

} // namespace std

#endif
