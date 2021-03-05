#include "jthread-main.t.hpp"

CASE("jthread: default construct")
{
    nonstd::jthread thr;

    EXPECT( thr.get_id() != std::this_thread::get_id() );
}

CASE("jthread: create thread with callback")
{
    nonstd::jthread thr{[]{} };

    EXPECT( thr.joinable() );
}
