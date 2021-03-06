// Copyright 2021-2021 by Martin Moene
//
// https://github.com/martinmoene/jthread-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_JTHREAD_LITE_H_INCLUDED
#define TEST_JTHREAD_LITE_H_INCLUDED

#include jthread_JTHREAD_HEADER

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

// Limit C++ Core Guidelines checking to GSL Lite:

#if _MSC_VER >= 1910
# include <CppCoreCheck/Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include <iostream>

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

// inline std::ostream & operator<<( std::ostream & os, xxx const & )
// {
// }

} // namespace nonstd

namespace lest {

// using ::nonstd::operator<<;
// using ::nonstd::operator==;

} // namespace lest

namespace std {

// using ::nonstd::operator<<;
// using ::nonstd::string::operator<<;

}

#define   lest_FEATURE_AUTO_REGISTER 1
#include "lest.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // TEST_JTHREAD_LITE_H_INCLUDED

// end of file
