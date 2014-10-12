#ifndef BARE_ALLOC_HPP
#define BARE_ALLOC_HPP

#include <cassert>
#include <bitset>
#include "bare_memory.hpp"

namespace bare {

/**
  * It implements the Allocator concept over
  * ExAllocatePoolWithTag.  
  *
  * Unlike STL it do not throws but returns nullptr instead.
  * It also uses tag to find memory leaks easily.
  */
template<
  class T,
  std::uint32_t blk_size_bytes = 1ULL << 10
>
class allocator
{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef decltype(blk_size_bytes) size_type;
  typedef std::uint32_t tag_type;

  template<class U> 
  struct rebind
  { 
    typedef allocator<U, pool_type> other; 
  };

  tag_type tag;

  allocator(tag_type a_tag) : tag(a_tag) {}

  template<class U>
  allocator(const allocator<U>& o) : tag(o.tag) {}

  //! Allocates n * sizeof(T) bytes
  //! If it fails thows std::bad_alloc.
  pointer allocate(size_type n)
  {
    assert(n > 0);
    //NB sizeof(T) > 0 for any T
    assert(2 ** 32 / sizeof(T) > n);

    return (pointer) ExAllocatePoolWithTag
      (pool_type, n * sizeof(T), tag); 
  }

  //! Deallocates the storage referenced by the pointer p,
  //! which must be a pointer obtained by an earlier call
  //! to allocate(). Uses ExFreePoolWithTag.
  //! Prereq: IRQL <= DISPATCH_LEVEL, see ExFreePoolWithTag.
  //! @param n is not used, 
  //! its just for compatibility with the Allocator concept.
  void deallocate(pointer p, size_type size)
  {
    ASSERT(p);
    ASSERT(size == sizeof(T));
    if (is_paged<pool_type>::value)
      PAGED_CODE();

    ExFreePoolWithTag(p, tag);
  }

  //! Constructs an object of type T 
  //! in allocated uninitialized storage pointed to by p, 
  //! using placement-new
  //! @param args are constructor argumets
  template<class U, class... Args>
  void construct(U* p, Args&&... args)
  {
    ASSERT(p != nullptr);
    if (is_paged<pool_type>::value)
      PAGED_CODE();

    ::new((void*)p) U(forward<Args>(args)...);
  }

  //! Calls the destructor of the object pointed to by p
  template<class U>
  void destroy(U* p)
  {
    ASSERT(p != nullptr);
    if (is_paged<pool_type>::value)
      PAGED_CODE();

    static_assert
      (!__has_virtual_destructor(U),
      "the argument of pool::allocator::destroy(U*) "
      "must not have a virtual destructor");
    p->U::~U();
  }


protected:
  static constexpr size_type storage_size_bytes = 
    blk_size_bytes;

  static constexpr std::uint8_t word_size_bytes = 8;

  static constexpr size_type element_size_words = 
    std::min(1, sizeof(T) / min_cell_size_bytes);

  static constexpr std::uint8_t cell_size_bytes = 
    element_size_words * word_size_bytes;

  static constexpr size_type storage_size_cells =
    storage_size_bytes 
      / (element_size_words * words_size_bytes);

  // 0 is free cell, 1 is used cell
  std::bitset<storage_size_cells> map;
  memory_block<T, storage_size_bytes / sizeof(T)>* storage;
};

} // bare

#endif
