#include <istream>
#include <bits/facets.h>

namespace std
{

template<class CharT, class Traits>
basic_istream<CharT, Traits>::sentry::sentry(basic_istream<CharT,Traits>& is,
                                     bool noskipws)
  : ok(false)
{
  if (!is.good()) {
    is.setstate(ios_base::failbit);
    return;
  }

  auto tied = is.tie();
  if (tied) 
    tied->flush();

  if (!noskipws) {
    auto& ctype_f = bits::facets::locale_independent::ctype<CharT>::facet; // TODO locales
    char ch;

    for (;;) {
      ch = is.peek();

      if (ch == Traits::eof()) {
        is.setstate(ios_base::eofbit | ios_base::failbit);
        return;
      }
      else if (!ctype_f.is(ctype<CharT>::space, ch))
        break;

      is.get(); // skip spaces
    }
  }
  ok = true;
}

template<class CharT, class Traits>
typename basic_istream<CharT, Traits>::int_type basic_istream<CharT, Traits>::get()
{
  gcount_ = 0;

  // FIXME try { (waits exceptions)
  typename basic_istream<CharT, Traits>::sentry sentry(*this, true);

  if (!sentry)
    return Traits::eof();

  int_type ch;

  auto* buf = this->rdbuf();
  if (buf && (ch = buf->sbumpc()) != Traits::eof()) {
    gcount_ = 1;
    return ch;
  }
  else {
    return Traits::eof();
  }
}

template<class CharT, class Traits>
typename basic_istream<CharT, Traits>::int_type basic_istream<CharT, Traits>::peek()
{
  gcount_ = 0;

  // FIXME try { (waits exceptions)
  typename basic_istream<CharT, Traits>::sentry sentry(*this, true);
  auto* buf = this->rdbuf();

  if (!sentry || !buf)
    return Traits::eof();

  return buf->sgetc();
}

#if 0
template<class CharT, class Traits>
basic_istream<CharT, Traits>& basic_istream<CharT, Traits>::unget()
{
  gcount_ = 0;

  // FIXME try { (waits exceptions)
  typename basic_istream<CharT, Traits>::sentry sentry(*this, true);
  auto* buf = this->rdbuf();

  if (!sentry || !buf)
    return *this;

  if (buf->sungetc() == Traits::eof())
    this->setstate(ios_base::badbit);
  return *this;
}
#endif

#if 0
template<class CharT, class Traits>
basic_istream<CharT, Traits>& basic_istream<CharT, Traits>
//
::operator>>(unsigned long& v)
{
//    try
//    {
        typename basic_istream<CharT, Traits>::sentry s(*this);
        if (s)
        {
            // The output goes directly into out's streambuffer
            using It = ::std::ostreambuf_iterator<CharT, Traits>;
            It it(*this);

            it = std::bits::facets::locale_independent::num_put<CharT, It>::facet
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
#endif

template class basic_istream<char>;

} // namespace std
