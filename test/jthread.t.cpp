#include "jthread-main.t.hpp"

CASE("jthread: default construct")
{
    nonstd::jthread thr;

    EXPECT( thr.get_id() != std::this_thread::get_id() );
}

CASE("jthread: create thread with callback - no parameters")
{
    int gx = 7;
    {
        nonstd::jthread thr{ [&]{ gx = 42; } };

        EXPECT( thr.joinable() );
    }
    EXPECT( gx == 42 );
}

CASE("jthread: create thread with callback - with parameters")
{
    int gx = 7;
    {
        nonstd::jthread thr{[&](int x, int y){ gx = x * y; }, 6, 7 };

        EXPECT( thr.joinable() );
    }
    EXPECT( gx == 42 );
}
