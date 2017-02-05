#include <ostream>
#include <locale>

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(unsigned long long v)
{
//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            // The output goes directly into out's streambuffer
            using It = ostreambuf_iterator<CharT, Traits>;
            It it(*this);

#ifndef _STD_LOCALES
            it = bits::facets::locale_independent::num_put<CharT, It>::facet
#else
	    it = use_facet<num_put<CharT, It> >(this->getloc())
#endif
              . put(it, *this, ' ', v);

            if (it.failed())
            {
//TODO                out.setstate(ios_base::badbit);
            }
        }
//    }
//    catch(...)
//    {
//TODO        out.setstate(ios_base::badbit); // can throw the exception
//    }
    return *this;
}

template class basic_ostream<char>;

} // namespace std
