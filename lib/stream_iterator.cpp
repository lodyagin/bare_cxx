#include <string>
#include <bits/stream_iterator.h>
#include <bits/ext_constr.h>

namespace std
{
namespace bits
{

template<>
_externally_constructed<dummy_streambuf<char, char_traits<char>>> dummy_streambuf_instance<char, char_traits<char>>
//
::instance /*__attribute__((weak))*/ {};

} // namespace bits
} // namespace std
