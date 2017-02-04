#include <locale>

namespace std {

ctype<char>::ctype(size_t refs) : locale::facet(refs)
{
    tab['\t'] |= space;
    tab['\n'] |= space;
    tab[11] |= space; // line tab
    tab[12] |= space; // form feed
    tab['\r'] |= space;
    tab[' '] |= space;
}

} // namespace std
