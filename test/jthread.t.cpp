#include "jthread-main.t.hpp"

namespace {

CASE("jthread: Allows to default-construct a jthread")
{
    nonstd::jthread thr;

    EXPECT( thr.get_id() != std::this_thread::get_id() );
}

CASE("jthread: Allows to create a thread with a callback - no parameters")
{
    int gx = 7;
    {
        nonstd::jthread thr{ [&]{ gx = 42; } };

        EXPECT( thr.joinable() );
    }
    EXPECT( gx == 42 );
}

CASE("jthread: Allows to create a thread with a callback - with parameters")
{
    int gx = 7;
    {
        nonstd::jthread thr{ [&](int x, int y){ gx = x * y; }, 6, 7 };

        EXPECT( thr.joinable() );
    }
    EXPECT( gx == 42 );
}

CASE("jthread: Allows to check if a thread is joinable")
{
    nonstd::jthread thr{ []{} };

    EXPECT( thr.joinable() );
}

CASE("jthread: Allows to join a thread")
{
    int gx = 7;
    nonstd::jthread thr{ [&](int x, int y){ gx = x * y; }, 6, 7 };

    thr.join();

    EXPECT( gx == 42 );
}

CASE("jthread: Allows to detach a thread")
{
    nonstd::jthread thr{ []{} };

    thr.detach();

    EXPECT_NOT( thr.joinable() );
}

CASE("jthread: Allows to obtain stop_source - stop_source not-implemented")
{
    nonstd::jthread thr{ []{} };

    nonstd::stop_source stop = thr.get_stop_source();
}

CASE("jthread: Allows to obtain stop_token - stop_token not-implemented")
{
    nonstd::jthread thr{ []{} };

    nonstd::stop_source ssrc = thr.get_stop_source();
}

CASE("jthread: Allows to request a thread to stop - stop_token not-implemented")
{
    nonstd::jthread thr{ []{} };

    // thr.request_stop();
}

CASE("jthread: Allows to swap two threads")
{
    nonstd::jthread t1{ []{} };
    nonstd::jthread t2{ []{} };

    nonstd::jthread::id tid1 = t1.get_id();
    nonstd::jthread::id tid2 = t2.get_id();

    swap( t1, t2 );

    EXPECT( t1.get_id() == tid2 );
    EXPECT( t2.get_id() == tid1 );
}

CASE("jthread: Allows to obtain a thread's id" "[.jthread][.info]")
{
    nonstd::jthread thr{ []{} };

    nonstd::jthread::id tid = thr.get_id();

    std::cout << "Info: get_id(): " << tid << "\n";
}

CASE("jthread: Allows to obtain a thread's native handle" "[.jthread][.info]")
{
    nonstd::jthread thr{ []{} };

    nonstd::jthread::native_handle_type tnh = thr.native_handle();

    std::cout << "Info: native_handle(): " << tnh << "\n";
}

CASE("jthread: Allows to obtain the maximum number of hardware threads" "[.jthread][.info]")
{
    std::cout << "Info: hardware_concurrency(): " << nonstd::jthread::hardware_concurrency() << "\n";
}

CASE("jthread: App" "[.jthread][.app]")
{
    int product = 0;
    const int six = 6;
    const int seven = 7;

    {
        nonstd::jthread thr{[&](int x, int y){ product = x * y; }, six, seven };

        // automatically join thread here, making sure it has executed:
    }

    std::cout << "App: Product of "<< six << " and " << seven << " is " << product << ".\n";
}

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if jthread_HAVE_TWEAK_HEADER
    EXPECT( jthread_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (jthread_HAVE_TWEAK_HEADER: 0)." );
#endif
}

} // anonymous namespace
