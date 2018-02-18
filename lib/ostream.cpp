#include <ostream>
#include <locale>

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(short v)
{
//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            using It = ostreambuf_iterator<CharT, Traits>;
            It it(*this);

#ifndef _STD_LOCALES
            auto& f = bits::facets::locale_independent::num_put<CharT, It>::facet;
#else
	    auto& f = use_facet<num_put<CharT, It> >(this->getloc());
#endif
            if (ios_base::flags() & ios_base::basefield & (ios_base::oct | ios_base::hex))
              it = f.put(it, *this, ' ', (unsigned long) (unsigned short) v);
            else
              it = f.put(it, *this, ' ', (long) v);

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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(unsigned short v)
{
//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            using It = ostreambuf_iterator<CharT, Traits>;
            It it(*this);

#ifndef _STD_LOCALES
            auto& f = bits::facets::locale_independent::num_put<CharT, It>::facet;
#else
	    auto& f = use_facet<num_put<CharT, It> >(this->getloc());
#endif
            it = f.put(it, *this, ' ', (unsigned long) v);

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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(int v)
{
//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            using It = ostreambuf_iterator<CharT, Traits>;
            It it(*this);

#ifndef _STD_LOCALES
            auto& f = bits::facets::locale_independent::num_put<CharT, It>::facet;
#else
	    auto& f = use_facet<num_put<CharT, It> >(this->getloc());
#endif
            if (ios_base::flags() & ios_base::basefield & (ios_base::oct | ios_base::hex))
              it = f.put(it, *this, ' ', (unsigned long) (unsigned int) v);
            else
              it = f.put(it, *this, ' ', (long) v);

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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(unsigned int v)
{
//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            using It = ostreambuf_iterator<CharT, Traits>;
            It it(*this);

#ifndef _STD_LOCALES
            auto& f = bits::facets::locale_independent::num_put<CharT, It>::facet;
#else
	    auto& f = use_facet<num_put<CharT, It> >(this->getloc());
#endif
            it = f.put(it, *this, ' ', (unsigned long) v);

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


template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(long v)
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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(unsigned long v)
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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::operator<<(long long v)
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

template<class CharT, class Traits>
basic_ostream<CharT, Traits>& basic_ostream<CharT, Traits>
//
::put(char_type ch)
{
  auto* buf = this->rdbuf();
  if (__builtin_expect(buf == nullptr, 0))
    return *this;

//    try
//    {
        typename basic_ostream<CharT, Traits>::sentry s(*this);
        if (s)
        {
          if (buf->sputc(ch) == Traits::eof())
            this->setstate(ios_base::badbit); // this function doesn't
                                              // set failbit by the standard
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
