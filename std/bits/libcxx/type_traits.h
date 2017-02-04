// This file contains a part of clang c++ library

/*
Copyright (c) 2009-2014 by the contributors listed in CREDITS.TXT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

//#include <bits/type_traits.h>

#define _VSTD std
#define _NOEXCEPT noexcept

namespace std {

struct __two {char __lx[2];};

// __is_referenceable  [defns.referenceable]

struct __is_referenceable_impl {
    template <class _Tp> static _Tp& __test(int);
    template <class _Tp> static __two __test(...);
};

template <class _Tp>
struct __is_referenceable : integral_constant<bool,
    !is_same<decltype(__is_referenceable_impl::__test<_Tp>(0)), __two>::value> {};


// add_const

template <class _Tp, bool = is_reference<_Tp>::value ||
                            is_function<_Tp>::value  ||
                            is_const<_Tp>::value     >
struct __add_const             {typedef _Tp type;};

template <class _Tp>
struct __add_const<_Tp, false> {typedef const _Tp type;};

template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY add_const
    {typedef typename __add_const<_Tp>::type type;};

template <class _Tp> using add_const_t = typename add_const<_Tp>::type;

// add_volatile

template <class _Tp, bool = is_reference<_Tp>::value ||
                            is_function<_Tp>::value  ||
                            is_volatile<_Tp>::value  >
struct __add_volatile             {typedef _Tp type;};

template <class _Tp>
struct __add_volatile<_Tp, false> {typedef volatile _Tp type;};

template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY add_volatile
    {typedef typename __add_volatile<_Tp>::type type;};

template <class _Tp> using add_volatile_t = typename add_volatile<_Tp>::type;

// add_cv

template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY add_cv
    {typedef typename add_const<typename add_volatile<_Tp>::type>::type type;};

template <class _Tp> using add_cv_t = typename add_cv<_Tp>::type;

// remove_reference

template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY remove_reference        {typedef _Tp type;};
template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY remove_reference<_Tp&>  {typedef _Tp type;};
template <class _Tp> struct _LIBCPP_TYPE_VIS_ONLY remove_reference<_Tp&&> {typedef _Tp type;};

template <class _Tp> using remove_reference_t = typename remove_reference<_Tp>::type;

// add_lvalue_reference

template <class _Tp, bool = __is_referenceable<_Tp>::value> struct __add_lvalue_reference_impl            { typedef _Tp  type; };
template <class _Tp                                       > struct __add_lvalue_reference_impl<_Tp, true> { typedef _Tp& type; };

template <class _Tp> struct add_lvalue_reference
{typedef typename __add_lvalue_reference_impl<_Tp>::type type;};

template <class _Tp> using add_lvalue_reference_t = typename add_lvalue_reference<_Tp>::type;

template <class _Tp, bool = __is_referenceable<_Tp>::value> struct __add_rvalue_reference_impl            { typedef _Tp   type; };
template <class _Tp                                       > struct __add_rvalue_reference_impl<_Tp, true> { typedef _Tp&& type; };

template <class _Tp> struct  add_rvalue_reference
{typedef typename __add_rvalue_reference_impl<_Tp>::type type;};

template <class _Tp> using add_rvalue_reference_t = typename add_rvalue_reference<_Tp>::type;

template <class _Tp> _Tp&& __declval(int);
template <class _Tp> _Tp   __declval(long);

template <class _Tp>
decltype(_VSTD::__declval<_Tp>(0))
declval() _NOEXCEPT;

struct __is_constructible_helper
{
    template <class _Tp>
    static std::true_type __test_ref(_Tp);
    template <class>
    static false_type __test_ref(...);

    template <class _Tp, class ..._Args,
        class = decltype(_Tp(_VSTD::declval<_Args>()...))>
    static true_type __test_nary(int);
    template <class _Tp, class...>
    static false_type __test_nary(...);

    //template <class _Tp, class _A0, class = decltype(::new _Tp(_VSTD::declval<_A0>()))>
    //static is_destructible<_Tp> __test_unary(int);
    template <class, class>
    static false_type __test_unary(...);
};

template <class _Tp, bool = is_void<_Tp>::value>
struct __is_default_constructible
    : decltype(__is_constructible_helper::__test_nary<_Tp>(0))
{};

template <class _Tp>
struct __is_default_constructible<_Tp, true> : false_type {};

template <class _Tp>
struct __is_default_constructible<_Tp[], false> : false_type {};

template <class _Tp, size_t _Nx>
struct __is_default_constructible<_Tp[_Nx], false>
    : __is_default_constructible<typename remove_all_extents<_Tp>::type>  {};

template <class _Tp, class... _Args>
struct __libcpp_is_constructible
{
  static_assert(sizeof...(_Args) > 1, "Wrong specialization");
  typedef decltype(__is_constructible_helper::__test_nary<_Tp, _Args...>(0))
      type;
};

template <class _Tp>
struct __libcpp_is_constructible<_Tp> : __is_default_constructible<_Tp> {};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp, _A0>
    : public decltype(__is_constructible_helper::__test_unary<_Tp, _A0>(0))
{};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp&, _A0>
    : public decltype(__is_constructible_helper::
    __test_ref<_Tp&>(_VSTD::declval<_A0>()))
{};

template <class _Tp, class _A0>
struct __libcpp_is_constructible<_Tp&&, _A0>
    : public decltype(__is_constructible_helper::
    __test_ref<_Tp&&>(_VSTD::declval<_A0>()))
{};

} // namespace bits


