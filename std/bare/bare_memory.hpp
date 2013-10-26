#ifndef BARE_MEMORY_HPP
#define BARE_MEMORY_HPP

#include <cstddef>

namespace bare {

// FIXME add overflow
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

template<uint8_t x>
struct pow2x
{
  enum { value = 2 * pow2x<x - 1>::value };
};

template<>
struct pow2x<0>
{
  enum { value = 1 };
};

//! Return mask with n lower bits set
template<uint8_t n, class T>
constexpr T n_bits_mask()
{
  return pow2x<n+1>::value - 1;
}

//TODO check errors with -fstrict-overflow
template<size_t n_bits, class word_t = uintmax_t>
class bitmap
{
public:
  constexpr static size_t size_in_bytes = 
    (n_bits - 1) / sizeof(word_t) + 1;

  constexpr static size_t reserved_in_bits = 
    size_in_bytes * 8;

  static_assert
	 (pow2x<log2x<n_bits>::value>::value == n_bits,
	  "bitmap: n_bits must be 2^n");

  static_assert
	 (n_bits % sizeof(word_t) % 8 == 0,
	  "bitmap: n_bits must be multiple of word_t");

  static_assert 
	 (reserved_in_bits == n_bits, 
	  "bitmap: reserved_in_bits == n_bits failed");

  //! A size in bits of a cell to store an index of bit
  //! inside word_t
  constexpr static uint8_t bit_idx_size = 
	 log2x<sizeof(word_t)*8>::value;

  //! log2(n_bits)
  constexpr static log2_n_bits = log2x<n_bits>::value;

  class iterator;

  class reference
  {
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

    bool operator == (const reference& b) const noexcept
    {
      return (bool)*this == (bool) b;
    }
  
    bool operator != (const reference& b) const noexcept
    {
      return !operator==(b);
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
  
  protected:
    reference(word_t* bm_ptr, size_t bit_idx) noexcept
      : m(bm_ptr), bit_addr(bit_idx) {};

    // TODO test with overlapping bitmaps
    bool is_same (const reference& b) const noexcept
    {
      if (bit_addr.shift != b.bit_addr.shift
          || __builtin_expect
               (bit_addr.carry != b.bit_addr.carry, 0)
          || __builtin_expect(m == b.m, 1))
        return false;

      // assert(bit_distance % sizeof(word_t) % 8 == 0);
      const ptrdiff_t word_distance = 
        bit_addr - b.bit_addr >> bit_idx_size;
      return word_distance == m - b.m;
    }

    bool is_less (const reference& b) const noexcept
    {
      return *this - b < 0;
    }

    bool is_greater (const reference& b) const noexcept
    {
      return *this - b > 0;
    }

    bool is_less_equal (const reference& b) const noexcept
    {
      return *this - b <= 0;
    }

    bool is_greater_equal (const reference& b) const noexcept
    {
      return *this - b >= 0;
    }

    void forward(ptrdiff_t n) noexcept
    {
      bit_addr += n;
    }

    reference& operator++ () noexcept
    {
      ++bit_addr;
      return *this;
    }

    // TODO test with overlapping bitmaps
    ptrdiff_t operator - (const reference& b) const
      noexcept
    {
      return bit_addr - b.bit_addr 
		  + (m - b.m << bit_idx_size);
    }

    word_t* m;

    struct bit_addr_t 
    {
      bit_addr_t(size_t idx) noexcept
        : cell(idx >> bit_idx_size),
          shift(idx - (cell << bit_idx_size)),
          mask((word_t)1 << shift),
			 carry(idx >> log2_n_bits)
      {}

      //! It cycles around the area. I think it is more
      //! safe has an infinite loop than has a data
      //! corruption. <NB> it covers also unused bits (in
      //! a case n_bits % sizeof(word_t) % 8 != 0
      bit_addr_t& operator ++ () noexcept
      {
        if (__builtin_expect(mask <<= 1, 1) == 0) {
          shift = 0; mask = 1;
          if (__builtin_expect
				   (++cell > size_in_bytes - 1, 0)) 
          {
            cell = 0;
				++carry;
          }
        }
        else {
          ++shift;
        }
        return *this;
      }

      //! See the notes for operator++()
      bit_addr_t& operator -- () noexcept
      {
        if (__builtin_expect(mask >>= 1, 1) == 0) {
          shift = 0; mask = (word_t) 1 << bit_idx_size - 1;
          if (__builtin_expect(cell-- == 0, 0)) 
			 {
            cell = size_in_bytes - 1;
				--carry;
          }
        }
        else {
          --shift;
        }
        return *this;
      }

      // TODO test with negative values
      bit_addr_t& operator += (ptrdiff_t n) noexcept
      {
        const int8_t shift_add = 
          n & n_bits_mask<bit_idx_size>();
        shift += shift_add;
        rol(mask, shift_add);
        const size_t div = cell + n; //, size_in_bytes);
		  cell = div 
          & n_bits_mask<log2_n_bits-bit_idx_size>();
		  carry = div >> log2_n_bits - 1;
        return &this;
      }

      // TODO test for negative values
      ptrdiff_t operator - (const bit_addr_t& b) const
        noexcept
      {
        return (carry - b.carry) * reserved_in_bits
          + (cell - b.cell) * sizeof(word_t) * 8
          + shift - b.shift;
      }

      size_t cell;
      uint8_t shift;
      word_t mask;
		// incremented or decremented with overlapping
		int8_t carry : bit_idx_size;
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
    bool operator == (const iterator& b) const noexcept
    { 
      return ref.is_same(b.ref);
    }
  
    bool operator != (const iterator& b) const noexcept
    {
      return !operator==(b);
    }

    bool operator < (const iterator& b) const noexcept
    {
      return ref.is_less(b.ref);
    }

    bool operator > (const iterator& b) const noexcept
    {
      return ref.is_greater(b.ref);
    }

    bool operator <= (const iterator& b) const noexcept
    {
      return ref.is_less_equal(b.ref);
    }

    bool operator >= (const iterator& b) const noexcept
    {
      return ref.is_greater_equal(b.ref);
    }

    reference operator * () noexcept { return ref; }

    const_reference operator * () const noexcept { return ref; }

    iterator& operator ++ () noexcept 
    { 
      ++ref; 
      return *this; 
    }

    iterator operator ++ (int) noexcept 
    { 
      iterator res(*this);
      ++(*this);
      return res; 
    }

    iterator& operator -- () noexcept 
    { 
      --ref; 
      return *this; 
    }

    iterator operator -- (int) noexcept 
    { 
      iterator res(*this);
      --(*this);
      return res; 
    }

    iterator& operator += (ptrdiff_t n) noexcept
    {
      ref.forward(n);
      return *this;
    }

    iterator& operator -= (ptrdiff_t n) noexcept
    {
      ref.forward(-n);
      return *this;
    }

    iterator operator + (ptrdiff_t n) const noexcept
    {
      iterator copy(*this);
      return copy += n;
    }

    iterator operator - (ptrdiff_t n) const noexcept
    {
      iterator copy(*this);
      return copy -= n;
    }

    ptrdiff_t operator - (const iterator& b) const
      noexcept
    {
      return distance(b);
    }

    reference operator [] (ptrdiff_t n) noexcept
    {
      return *(*this + n);
    }

    const_reference operator [] (ptrdiff_t n) const
      noexcept 
    {
      return *(*this + n);
    }

  private:
    iterator(word_t* bm_ptr, size_t bit_idx) noexcept
		: ref(bm_ptr, bit_idx) {}
    reference ref;
  };

  typedef const iterator const_iterator;

  bitmap() noexcept : bm(bm_), end_it(begin()) {}

  // TODO do not need deep copy bm_ if bm != bm_ 
  bitmap(const bitmap& b) noexcept = default;

  // TODO do not need deep copy bm_ if bm != bm_ 
  bitmap& operator=(const bitmap& b) noexcept = default;

  //! Need skip not used bits in the last cell
  bool operator == (const bitmap&) noexcept = delete;

  //! Need skip not used bits in the last cell
  bool operator != (const bitmap&) noexcept = delete;

  // disabled for safety
  // void swap(bitmap& b) ?noexcept
  
  size_type size() const noexcept
  {
	 const size_t sz = end() - begin();
	 if (__builtin_expect(sz <= n_bits, 1))
		return sz;
	 else
		return max_size();
  }

  size_type max_size() const noexcept
  {
	 return n_bits;
  }

  bool empty() const noexcept
  {
	 return begin() == end();
  }

  iterator begin() noexcept
  {
    return iterator(bm, 0);
  }

  const_iterator begin() const noexcept
  {
    return iterator(bm, 0);
  }

  const_iterator cbegin() noexcept
  {
	 return const_cast<const bitmap*>(this)->begin();
  }

  iterator end() noexcept
  {
    return end_it;
  }

  const_iterator end() const noexcept
  {
    return end_it;
  }

  const_iterator cend() noexcept
  {
	 return const_cast<const bitmap*>(this)->end();
  }

private:
  word_t bm_[size_in_bytes];
  word_t* bm;
  iterator end_it;
};

template<size_t n_bits, class word_t = uintmax_t>
typename bitmap<n_bits, word_t>::iterator 
operator + 
  (ptrdiff_t n, 
   const typename bitmap<n_bits, word_t>::iterator& it
   )  noexcept
{
  return it.operator+(n);
}


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
