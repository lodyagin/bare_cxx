#ifndef BARE_MEMORY_HPP
#define BARE_MEMORY_HPP

#include <cstdint>

typedef uint64_t size_t;
typedef int64_t ptrdiff_t;

namespace bare {

template<uintmax_t x>
struct log2x 
{
  enum { value = log2x<(x >> 1)>::value + 1 };
};

template<> 
struct log2x<1>
{
  enum { value = 0 };
};

template<size_t n_bits>
class bitmap
{
  typedef uintmax_t word_t;

  word_t bm[(n_bits - 1) / sizeof(word_t) + 1] = {0};

public:
  class reference
  {
    friend bitmap;
    friend class iterator;
  public:
    //! Assigns a value to the referenced bit.
    reference& operator=(bool b) noexcept
    {
      (m[bit_addr.cell] &= ~bit_addr.mask)
        |= (word_t) b << bit_addr.shift;
      return *this;
    }

    //! Assigns a value to the referenced bit.
    reference& operator=(const reference& r) noexcept
    {
      bit_addr = r.bit_addr;
      return *this;
    }

    //! Returns the value of the referenced bit. 
    operator bool() const noexcept
    {
      return m[bit_addr.cell] & bit_addr.mask;
    }

    //! Returns the inverse of the referenced bit. 
    bool operator ~ () const noexcept
    {
      return ! operator bool();
    }

    //! Inverts the referenced bit. 
    reference& flip() noexcept
    {
      m[bit_addr.cell] ^= bit_addr.mask;
      return *this;
    }

  private:
    reference(word_t* bm_ptr, size_t bit_idx) 
      : m(bm_ptr), bit_addr(bit_idx) {};

    reference& operator++ ()
    {
      ++bit_addr;
      return *this;
    }

    word_t* m;

    struct bit_addr_t 
    {
      template<class T>
      struct bit_idx_size_ { enum { value = log2x<sizeof(T)*8>::value }; };

      //! A size in bits of a cell to store an index of bit inside word_t
      constexpr static uint8_t bit_idx_size = bit_idx_size_<word_t>::value;

      bit_addr_t(size_t idx)
        : cell(idx >> bit_idx_size),
          shift(idx - (cell << bit_idx_size)),
          mask((word_t)1 << shift)
      {}

      bit_addr_t& operator ++ ()
      {
        // TODO add unlikely
        if ((mask <<= 1) == 0) {
          cell++; shift = 0; mask = 1;
        }
        else {
          shift++;
        }
        return *this;
      }

      size_t cell;
      uint8_t shift;
      word_t mask;
    } bit_addr;
  };

  typedef bool value_type;
  typedef const reference const_reference;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  
  class iterator
  {
    friend bitmap;
  public:
    reference operator * () noexcept { return ref; }
    const_reference operator * () const noexcept { return ref; }
    iterator& operator ++ () noexcept { ++ref; return *this; }
  private:
    iterator(word_t* bm_ptr, size_t bit_idx) : ref(bm_ptr, bit_idx) {}
    reference ref;
  };

  typedef const iterator const_iterator;

  iterator begin()
  {
    return iterator(bm, 0);
  }

  iterator end()
  {
    return iterator(bm, n_bits + 1);
  }

protected:
};

template<>
class bitmap<0> {};

#if 0
class memory_block
{
public:
  memory_block(void* start, size_t sz)
    : start_addr(start), size(sz) 
  {}

  void* start_addr;
  size_t size;
};
#else
template<class Cell, size_t N>
class memory_block
{
public:
  //void* address() { return b; }
  //const void* address() const { return b; }

protected:

  //! The storage
  Cell storage[N];
};
#endif

};

#endif
