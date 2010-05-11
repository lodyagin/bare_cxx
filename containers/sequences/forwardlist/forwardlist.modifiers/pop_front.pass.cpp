//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <forward_list>

// void pop_front();

#include <forward_list>
#include <cassert>

#include "../../../MoveOnly.h"

int main()
{
    {
        typedef int T;
        typedef std::forward_list<T> C;
        typedef std::forward_list<T> C;
        C c;
        c.push_front(1);
        c.push_front(3);
        c.pop_front();
        assert(distance(c.begin(), c.end()) == 1);
        assert(c.front() == 1);
        c.pop_front();
        assert(distance(c.begin(), c.end()) == 0);
    }
#ifdef _LIBCPP_MOVE
    {
        typedef MoveOnly T;
        typedef std::forward_list<T> C;
        C c;
        c.push_front(1);
        c.push_front(3);
        c.pop_front();
        assert(distance(c.begin(), c.end()) == 1);
        assert(c.front() == 1);
        c.pop_front();
        assert(distance(c.begin(), c.end()) == 0);
    }
#endif
}
