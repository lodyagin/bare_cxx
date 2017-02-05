#include <bare/video>

namespace bare
{
namespace video
{

template<>
char basic_streambuf<char, std::char_traits<char>, 64>::in_buf[64] {};

}
}
