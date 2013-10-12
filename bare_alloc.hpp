#ifndef BARE_ALLOC_HPP
#define BARE_ALLOC_HPP

#include "bare_memory.hpp"

namespace bare {

template<class T>
class allocator
{
public:
  typedef T  value_type;
  typedef T* pointer;

  allocator(memory_block& blk) : block(&blk) {}

  pointer allocate(size_t n)
  {
    
  }

protected:
  memory_block* block;
};

};

#endif
