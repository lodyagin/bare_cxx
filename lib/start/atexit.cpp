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

#include <cstddef>
#include <array>
#include <iterator>
#include <algorithm>
#include <bits/ext_constr.h>

using namespace std;
using namespace bits;

template<size_t size>
class _atexit_array_t
{
public:
  struct info
  {
    void (*destructor) (void*);
    void *obj;
    void *dso;
  };
  using atex_type = array<info, size>;
  using reverse_it = reverse_iterator
    <atex_type::iterator>;

  int reg
    ( void (*destructor) (void*), 
      void *arg,
      void *dso )
  {
    if (next == atex.end())
      return -1; // no space in the table
    *next++ = {destructor, obj, dso};
    return 0;
  }

  void call(void* dso)
  {
    if (dso == nullptr) {
      for_each
        ( reverse_it(next), atex.rbegin(),
          [](info& i)
          {
            if (i.destructor) {
              (*i.destructor) (i.obj);
              i.destructor = nullptr;
            }
          });     
    }
    else {
      for_each
        ( reverse_it(next), atex.rbegin(),
          [](info& i)
          {
            if (i.dso == dso && i.destructor) {
              (*i.destructor) (i.obj);
              i.destructor = nullptr;
            }
          });
    }     
  }

protected:
  atex_type atex = { 0 };
  atex_type::iterator next = atex.begin();
};

static _externally_constructed<_atexit_array_t<64>> 
  _atexit_array; 

// it should countain the uniq value per dl module
void *__dso_handle = &_atexit_array;

inline static _atexit_array_init()
{
  // is thread-protected by compiler (compare to out-of
  // function scope)?
  static bool inited = false;
  if (__builting_expect(!inited, 0)) {
    new(&_atexit_array.m) declspec(_atexit_array.m);
    inited = true;
  }
}

extern "C" int __cxa_atexit
  ( void (*destructor) (void*), 
    void *arg,
    void *dso
   )
{
  _atexit_array_init();
  return _atexit_array.m.reg(destructor, arg, dso);
}

extern "C" void __cxa_finalize(void* dso)
{
  _atexit_array_init();
  _atexit_array.m.call(dso);
}
