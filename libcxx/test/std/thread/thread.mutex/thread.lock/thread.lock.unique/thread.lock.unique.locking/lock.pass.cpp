//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
// ALLOW_RETRIES: 2

// TODO(ldionne): This test fails on Ubuntu Focal on our CI nodes (and only there), in 32 bit mode.
// UNSUPPORTED: linux && 32bits-on-64bits

// <mutex>

// template <class Mutex> class unique_lock;

// void lock();

#include <mutex>
#include <thread>
#include <cstdlib>
#include <cassert>

#include "make_test_thread.h"
#include "test_macros.h"

std::mutex m;

typedef std::chrono::system_clock Clock;
typedef Clock::time_point time_point;
typedef Clock::duration duration;
typedef std::chrono::milliseconds ms;
typedef std::chrono::nanoseconds ns;

void f()
{
    std::unique_lock<std::mutex> lk(m, std::defer_lock);
    time_point t0 = Clock::now();
    lk.lock();
    time_point t1 = Clock::now();
    assert(lk.owns_lock() == true);
    ns d = t1 - t0 - ms(250);
    assert(d < ms(25));  // within 25ms
#ifndef TEST_HAS_NO_EXCEPTIONS
    try
    {
        lk.lock();
        assert(false);
    }
    catch (std::system_error& e)
    {
        assert(e.code().value() == EDEADLK);
    }
#endif
    lk.unlock();
    lk.release();
#ifndef TEST_HAS_NO_EXCEPTIONS
    try
    {
        lk.lock();
        assert(false);
    }
    catch (std::system_error& e)
    {
        assert(e.code().value() == EPERM);
    }
#endif
}

int main(int, char**)
{
    m.lock();
    std::thread t = support::make_test_thread(f);
    std::this_thread::sleep_for(ms(250));
    m.unlock();
    t.join();

  return 0;
}
