//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// class multimap

//       iterator find(const key_type& k);
// const_iterator find(const key_type& k) const;

#include <map>
#include <cassert>

int main()
{
    typedef std::pair<const int, double> V;
    typedef std::multimap<int, double> M;
    {
        typedef M::iterator R;
        V ar[] =
        {
            V(5, 1),
            V(5, 2),
            V(5, 3),
            V(7, 1),
            V(7, 2),
            V(7, 3),
            V(9, 1),
            V(9, 2),
            V(9, 3)
        };
        M m(ar, ar+sizeof(ar)/sizeof(ar[0]));
        R r = m.find(5);
        assert(r == m.begin());
        r = m.find(6);
        assert(r == m.end());
        r = m.find(7);
        assert(r == next(m.begin(), 3));
        r = m.find(8);
        assert(r == m.end());
        r = m.find(9);
        assert(r == next(m.begin(), 6));
        r = m.find(10);
        assert(r == m.end());
    }
    {
        typedef M::const_iterator R;
        V ar[] =
        {
            V(5, 1),
            V(5, 2),
            V(5, 3),
            V(7, 1),
            V(7, 2),
            V(7, 3),
            V(9, 1),
            V(9, 2),
            V(9, 3)
        };
        const M m(ar, ar+sizeof(ar)/sizeof(ar[0]));
        R r = m.find(5);
        assert(r == m.begin());
        r = m.find(6);
        assert(r == m.end());
        r = m.find(7);
        assert(r == next(m.begin(), 3));
        r = m.find(8);
        assert(r == m.end());
        r = m.find(9);
        assert(r == next(m.begin(), 6));
        r = m.find(10);
        assert(r == m.end());
    }
}
