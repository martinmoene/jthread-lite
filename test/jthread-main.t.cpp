// Copyright 2021-2021 by Martin Moene
//
// https://github.com/martinmoene/thread-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "jthread-main.t.hpp"

// C++ language version (represent 98 as 3):

#define jthread_CPLUSPLUS_V  ( jthread_CPLUSPLUS / 100 - (jthread_CPLUSPLUS > 200000 ? 2000 : 1994) )

// Compiler versions:

// MSVC++  6.0  _MSC_VER == 1200  jthread_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  jthread_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  jthread_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  jthread_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  jthread_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  jthread_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  jthread_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  jthread_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  jthread_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  jthread_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  jthread_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#if 0

#if defined(_MSC_VER ) && !defined(__clang__)
# define jthread_COMPILER_MSVC_VER           (_MSC_VER )
# define jthread_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define jthread_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define jthread_COMPILER_MSVC_VER           0
# define jthread_COMPILER_MSVC_VERSION       0
# define jthread_COMPILER_MSVC_VERSION_FULL  0
#endif

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

#if defined(__GNUC__) && !defined(__clang__)
# define jthread_COMPILER_GNUC_VERSION jthread_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define jthread_COMPILER_GNUC_VERSION 0
#endif

#endif

#define jthread_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define jthread_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "thread-lite version" "[.string][.version]" )
{
    jthread_PRESENT( jthread_lite_MAJOR   );
    jthread_PRESENT( jthread_lite_MINOR   );
    jthread_PRESENT( jthread_lite_PATCH   );
    jthread_PRESENT( jthread_lite_VERSION );

    // jthread_PRESENT( jthread_CPP98_FALLBACK );
}

CASE( "thread-lite configuration" "[.string][.config]" )
{
    jthread_PRESENT( jthread_CPLUSPLUS );
    jthread_PRESENT( jthread_CPLUSPLUS_V );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    jthread_PRESENT( __cplusplus );

#if _MSVC_LANG
    jthread_PRESENT( _MSVC_LANG );
#else
    jthread_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
    jthread_PRESENT( jthread_COMPILER_APPLECLANG_VERSION );
    jthread_PRESENT( jthread_COMPILER_CLANG_VERSION );
    jthread_PRESENT( jthread_COMPILER_GNUC_VERSION );
    jthread_PRESENT( jthread_COMPILER_MSVC_VERSION );
    jthread_PRESENT( jthread_COMPILER_MSVC_VERSION_FULL );
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
    jthread_PRESENT( jthread_HAVE_CONSTEXPR_11 );
    jthread_PRESENT( jthread_HAVE_DEFAULT_FN_TPL_ARGS );
    jthread_PRESENT( jthread_HAVE_EXPLICIT_CONVERSION );
    jthread_PRESENT( jthread_HAVE_NODISCARD );
    jthread_PRESENT( jthread_HAVE_NOEXCEPT );
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if defined(_HAS_CPP0X) && _HAS_CPP0X
    jthread_PRESENT( _HAS_CPP0X );
#else
    jthread_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++98 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++03 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++0x -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++11 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++14 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++17 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass

cl -EHsc -I../include string-main.t.cpp && string-main.t.exe --pass
#endif

// end of file
