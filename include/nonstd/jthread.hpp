//
// Copyright (c) 2021-2021 Martin Moene
//
// https://github.com/martinmoene/jthread-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NONSTD_JTHREAD_LITE_HPP
#define NONSTD_JTHREAD_LITE_HPP

#define jthread_lite_MAJOR  0
#define jthread_lite_MINOR  0
#define jthread_lite_PATCH  0

#define jthread_lite_VERSION  jthread_STRINGIFY(jthread_lite_MAJOR) "." jthread_STRINGIFY(jthread_lite_MINOR) "." jthread_STRINGIFY(jthread_lite_PATCH)

#define jthread_STRINGIFY(  x )  jthread_STRINGIFY_( x )
#define jthread_STRINGIFY_( x )  #x

// tweak header support:

#ifdef __has_include
# if __has_include(<nonstd/jthread.tweak.hpp>)
#  include <nonstd/jthread.tweak.hpp>
# endif
#define jthread_HAVE_TWEAK_HEADER  1
#else
#define jthread_HAVE_TWEAK_HEADER  0
//# pragma message("jthread.hpp: Note: Tweak header not supported.")
#endif

// Control presence of exception handling (try and auto discover):

#ifndef jthread_CONFIG_NO_EXCEPTIONS
# if _MSC_VER
# include <cstddef>     // for _HAS_EXCEPTIONS
# endif
# if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || (_HAS_EXCEPTIONS)
#  define jthread_CONFIG_NO_EXCEPTIONS  0
# else
#  define jthread_CONFIG_NO_EXCEPTIONS  1
# endif
#endif

// TODO Switch between nonstd and std version of jthread:

#define  jthread_CONFIG_SELECT_JTHREAD_NONSTD    1
#define  jthread_CONFIG_SELECT_JTHREAD_STD       2

#ifndef  jthread_CONFIG_SELECT_JTHREAD
# define jthread_CONFIG_SELECT_JTHREAD jthread_CONFIG_SELECT_JTHREAD_NONSTD
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   jthread_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define jthread_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define jthread_CPLUSPLUS  __cplusplus
# endif
#endif

#define jthread_CPP98_OR_GREATER  ( jthread_CPLUSPLUS >= 199711L )
#define jthread_CPP11_OR_GREATER  ( jthread_CPLUSPLUS >= 201103L )
#define jthread_CPP14_OR_GREATER  ( jthread_CPLUSPLUS >= 201402L )
#define jthread_CPP17_OR_GREATER  ( jthread_CPLUSPLUS >= 201703L )
#define jthread_CPP20_OR_GREATER  ( jthread_CPLUSPLUS >= 202000L )
#define jthread_CPP23_OR_GREATER  ( jthread_CPLUSPLUS >= 202300L )

// MSVC version:

#if defined(_MSC_VER ) && !defined(__clang__)
# define jthread_COMPILER_MSVC_VER           (_MSC_VER )
# define jthread_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define jthread_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define jthread_COMPILER_MSVC_VER           0
# define jthread_COMPILER_MSVC_VERSION       0
# define jthread_COMPILER_MSVC_VERSION_FULL  0
#endif

// clang version:

#define jthread_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define jthread_COMPILER_APPLECLANG_VERSION jthread_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define jthread_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define jthread_COMPILER_APPLECLANG_VERSION 0
# define jthread_COMPILER_CLANG_VERSION jthread_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define jthread_COMPILER_APPLECLANG_VERSION 0
# define jthread_COMPILER_CLANG_VERSION 0
#endif

// GNUC version:

#if defined(__GNUC__) && !defined(__clang__)
# define jthread_COMPILER_GNUC_VERSION jthread_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define jthread_COMPILER_GNUC_VERSION 0
#endif

// half-open range [lo..hi):
#define jthread_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

#define jthread_CPP11_100  (jthread_CPP11_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1600)
#define jthread_CPP11_110  (jthread_CPP11_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1700)
#define jthread_CPP11_120  (jthread_CPP11_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1800)
#define jthread_CPP11_140  (jthread_CPP11_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1900)
#define jthread_CPP11_141  (jthread_CPP11_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1910)

#define jthread_CPP11_000  (jthread_CPP11_OR_GREATER)

#define jthread_CPP14_000  (jthread_CPP14_OR_GREATER)
#define jthread_CPP14_120  (jthread_CPP14_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1800)

#define jthread_CPP17_000  (jthread_CPP17_OR_GREATER)
#define jthread_CPP17_120  (jthread_CPP17_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1800)
#define jthread_CPP17_140  (jthread_CPP17_OR_GREATER || jthread_COMPILER_MSVC_VER >= 1900)

#define jthread_CPP20_000  (jthread_CPP20_OR_GREATER)

// Presence of C++11 language features:

#define jthread_HAVE_CONSTEXPR_11           (jthread_CPP11_000 && !jthread_BETWEEN(jthread_COMPILER_MSVC_VER, 1, 1910))
#define jthread_HAVE_NOEXCEPT                jthread_CPP11_140
#define jthread_HAVE_NULLPTR                 jthread_CPP11_100
#define jthread_HAVE_DEFAULT_FN_TPL_ARGS     jthread_CPP11_120
#define jthread_HAVE_EXPLICIT_CONVERSION     jthread_CPP11_120

// Presence of C++14 language features:

#define jthread_HAVE_CONSTEXPR_14            jthread_CPP14_000

// Presence of C++17 language features:

#define jthread_HAVE_DEDUCTION_GUIDES        jthread_CPP17_000
#define jthread_HAVE_INLINE_VAR              jthread_CPP17_000
#define jthread_HAVE_NODISCARD               jthread_CPP17_000

// Presence of C++20 language features:

// none

// Presence of C++ library features:

#define jthread_HAVE_TYPE_TRAITS             jthread_CPP11_110

// Usage of C++ language features:

#if jthread_HAVE_CONSTEXPR_11
# define jthread_constexpr constexpr
#else
# define jthread_constexpr /*constexpr*/
#endif

#if jthread_HAVE_CONSTEXPR_14
# define jthread_constexpr14  constexpr
#else
# define jthread_constexpr14  /*constexpr*/
#endif

#if jthread_HAVE_EXPLICIT_CONVERSION
# define jthread_explicit  explicit
#else
# define jthread_explicit  /*explicit*/
#endif

#if jthread_HAVE_NOEXCEPT && !jthread_CONFIG_NO_EXCEPTIONS
# define jthread_noexcept noexcept
# define jthread_noexcept_op(expr) noexcept(expr)
#else
# define jthread_noexcept /*noexcept*/
# define jthread_noexcept_op(expr) /*noexcept(expr)*/
#endif

#if jthread_HAVE_NODISCARD
# define jthread_nodiscard [[nodiscard]]
#else
# define jthread_nodiscard /*[[nodiscard]]*/
#endif

#if jthread_HAVE_NULLPTR
# define jthread_nullptr nullptr
#else
# define jthread_nullptr NULL
#endif

#if jthread_HAVE_EXPLICIT_CONVERSION
# define jthread_explicit_cv explicit
#else
# define jthread_explicit_cv /*explicit*/
#endif

#include <condition_variable>
#include <thread>
#include <type_traits>

#if 0
namespace nonstd {

    // 32.3.3 class stop_token
    class stop_token;

    // 32.3.4 class stop_source
    class stop_source;

    // no-shared-stop-state indicator
    struct nostopstate_t {
        explicit nostopstate_t() = default;
    };

    inline jthread_constexpr nostopstate_t nostopstate{};

    // 32.3.5 class stop_callback
    template<class Callback>
    class stop_callback;
} // namespace std
#endif

namespace nonstd {

//
// class stop_token:
//

class stop_token
{
public:

    // 32.3.3.1, constructors, copy, and assignment

    stop_token() jthread_noexcept;
    stop_token(const stop_token&) jthread_noexcept;
    stop_token(stop_token&&) jthread_noexcept;

    stop_token& operator=(const stop_token&) jthread_noexcept;
    stop_token& operator=(stop_token&&) jthread_noexcept;

    ~stop_token();

    void swap(stop_token&) jthread_noexcept;

    // 32.3.3.2, stop handling

    jthread_nodiscard bool stop_requested() const jthread_noexcept;
    jthread_nodiscard bool stop_possible() const jthread_noexcept;

    jthread_nodiscard friend bool operator==(const stop_token& lhs, const stop_token& rhs) jthread_noexcept
    {
        return false;   // [[nodiscard]] friend...: must occur with definition.
    }

    friend void swap(stop_token& lhs, stop_token& rhs) jthread_noexcept;
};

//
// no-shared-stop-state indicator
//

struct nostopstate_t
{
    explicit nostopstate_t() = default;
};

#if jthread_HAVE_INLINE_VAR
inline jthread_constexpr nostopstate_t nostopstate{};
#else
# define nostopstate nostopstate_t{}
#endif

//
// class stop_source:
//

class stop_source
{
public:
    // 32.3.4.1, constructors, copy, and assignment

    stop_source()
    {}

    explicit stop_source(nostopstate_t) jthread_noexcept
    {}

    stop_source(const stop_source&) jthread_noexcept;
    stop_source(stop_source&&) jthread_noexcept;

    stop_source& operator=(const stop_source&) jthread_noexcept;
    stop_source& operator=(stop_source&&) jthread_noexcept;

    ~stop_source()
    {}

    void swap(stop_source&) jthread_noexcept;

    // 32.3.4.2, stop handling

    jthread_nodiscard stop_token get_token() const jthread_noexcept;
    jthread_nodiscard bool stop_possible() const jthread_noexcept;
    jthread_nodiscard bool stop_requested() const jthread_noexcept;

    bool request_stop() jthread_noexcept;

    jthread_nodiscard friend bool operator==(const stop_source& lhs, const stop_source& rhs) jthread_noexcept
    {
        return false;   // [[nodiscard]] friend...: must occur with definition.
    }

    friend void swap(stop_source& lhs, stop_source& rhs) jthread_noexcept;
};

//
// class stop_callback:
//

template<class Callback>
class stop_callback
{
public:
    using callback_type = Callback;

    // 32.3.5.1, constructors and destructor

    template<class C>
    explicit stop_callback(const stop_token& st, C&& cb)
        jthread_noexcept_op((std::is_nothrow_constructible<Callback, C>::value));

    template<class C>
    explicit stop_callback(stop_token&& st, C&& cb)
        jthread_noexcept_op((std::is_nothrow_constructible<Callback, C>::value));

    ~stop_callback();

    stop_callback(const stop_callback&) = delete;
    stop_callback(stop_callback&&) = delete;
    stop_callback& operator=(const stop_callback&) = delete;
    stop_callback& operator=(stop_callback&&) = delete;

private:
    Callback callback; // exposition only
};

#if jthread_HAVE_DEDUCTION_GUIDES
    template<class Callback>
    stop_callback(stop_token, Callback) -> stop_callback<Callback>;
#endif

template<class Callback>
auto make_stop_callback(stop_token && st, Callback && cb) -> stop_callback<Callback>
{
    return stop_callback<Callback>{std::move(st), std::forward<Callback>(cb)};
}

//
// class condition_variable_any:
//

class condition_variable_any
{
public:
    condition_variable_any();
    ~condition_variable_any();
    condition_variable_any(const condition_variable_any&) = delete;
    condition_variable_any& operator=(const condition_variable_any&) = delete;

    void notify_one() jthread_noexcept;
    void notify_all() jthread_noexcept;

    // 32.6.4.1, noninterruptible waits

    template<class Lock>
    void wait(Lock& lock);

    template<class Lock, class Predicate>
    void wait(Lock& lock, Predicate pred);

    template<class Lock, class Clock, class Duration>
    std::cv_status wait_until(Lock& lock, const std::chrono::time_point<Clock, Duration>& abs_time);

    template<class Lock, class Clock, class Duration, class Predicate>
    bool wait_until(Lock& lock, const std::chrono::time_point<Clock, Duration>& abs_time, Predicate pred);

    template<class Lock, class Rep, class Period>
    std::cv_status wait_for(Lock& lock, const std::chrono::duration<Rep, Period>& rel_time);

    template<class Lock, class Rep, class Period, class Predicate>
    bool wait_for(Lock& lock, const std::chrono::duration<Rep, Period>& rel_time, Predicate pred);

    // 32.6.4.2, interruptible waits

    template<class Lock, class Predicate>
    bool wait(Lock& lock, stop_token stoken, Predicate pred);

    template<class Lock, class Clock, class Duration, class Predicate>
    bool wait_until(Lock& lock, stop_token stoken, const std::chrono::time_point<Clock, Duration>& abs_time, Predicate pred);

    template<class Lock, class Rep, class Period, class Predicate>
    bool wait_for(Lock& lock, stop_token stoken, const std::chrono::duration<Rep, Period>& rel_time, Predicate pred);
};

//
// class jthread:
//

class jthread
{
public:
    // types:

    using id = std::thread::id;
    using native_handle_type = std::thread::native_handle_type;

    // 32.4.3.1, constructors, move, and assignment

    jthread() jthread_noexcept
        : m_ssource{ nostopstate }
    {}

    template< class F, class... Args >
    explicit jthread( F && f, Args &&... args )
        : m_ssource{ nostopstate }  // TODO m_ssource{}
        , m_thread{ ::std::forward<decltype(f)>(f), ::std::forward<decltype(args)>(args)... }
    {}

    ~jthread()
    {
        if ( joinable() )
        {
            // TODO request_stop();
            join();
        }
    }

    jthread( jthread const &) = delete;
    jthread( jthread && other ) jthread_noexcept = default;

    jthread & operator=( jthread const & ) = delete;

    jthread & operator=( jthread && thr ) jthread_noexcept
    {
        // if not joined/detached, signal stop and wait for end:
        if ( joinable() )
        {
            // TODO request_stop();
            join();
        }

        m_thread  = std::move( thr.m_thread  );
        m_ssource = std::move( thr.m_ssource );

        return *this;
    }

    // 32.4.3.2, members

    void swap( jthread & other ) jthread_noexcept
    {
        using std::swap;
        swap( m_ssource, other.m_ssource );
        swap( m_thread , other.m_thread  );
    }

    jthread_nodiscard bool joinable() const jthread_noexcept
    {
        return m_thread.joinable();
    }

    void join()
    {
        m_thread.join();
    }

    void detach()
    {
        m_thread.detach();
    }

    jthread_nodiscard id get_id() const jthread_noexcept
    {
         return m_thread.get_id();
    }

    jthread_nodiscard native_handle_type native_handle()
    {
        // see 32.2.3
        return m_thread.native_handle();
    }

    // 32.4.3.3, stop token handling

    jthread_nodiscard stop_source get_stop_source() jthread_noexcept
    {
        return m_ssource;
    }

    jthread_nodiscard stop_token get_stop_token() const jthread_noexcept
    {
        return m_ssource.get_token();
    }

    bool request_stop() jthread_noexcept
    {
        return m_ssource.request_stop();
    }

    // 32.4.3.4, specialized algorithms

    friend void swap(jthread& lhs, jthread& rhs) jthread_noexcept
    {
        lhs.swap( rhs );
    }

    // 32.4.3.5, static members

    jthread_nodiscard static unsigned int hardware_concurrency() jthread_noexcept;

private:
    stop_source m_ssource;  // not used yet
    std::thread m_thread{};
};

} // namespace std

#endif // NONSTD_JTHREAD_LITE_HPP
