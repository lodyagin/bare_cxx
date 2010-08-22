//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <memory>

// unique_ptr

// test get_deleter()

#include <memory>
#include <cassert>

struct Deleter
{
    void operator()(void*) {}

    int test() {return 5;}
    int test() const {return 6;}
};

int main()
{
    {
    std::unique_ptr<int[], Deleter> p;
    assert(p.get_deleter().test() == 5);
    }
    {
    const std::unique_ptr<int[], Deleter> p;
    assert(p.get_deleter().test() == 6);
    }
}
