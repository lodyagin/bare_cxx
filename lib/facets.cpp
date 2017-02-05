#include <bits/facets.h>

namespace std
{
namespace bits
{

template<>
::std::ctype<char> facets::locale_independent::ctype<char>::facet {};
  
template<>
::std::num_put<char, std::ostreambuf_iterator<char>> facets::
locale_independent::num_put<char, std::ostreambuf_iterator<char>>
//
::facet {};

} // namespace bits
} // namespace std
