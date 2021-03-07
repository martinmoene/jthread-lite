# jthread lite: C++20's jthread for C++11 and later

A work in its infancy. Suggested by Peter Featherstone.

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/jthread-lite.svg?branch=master)](https://travis-ci.org/martinmoene/jthread-lite) [![Build status](https://ci.appveyor.com/api/projects/status/nrnbfhvvp39ex075?svg=true)](https://ci.appveyor.com/project/martinmoene/jthread-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fjthread-lite.svg)](https://github.com/martinmoene/jthread-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/jthread-lite/master/include/nonstd/jthread.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)]() [![Try it online](https://img.shields.io/badge/on-wandbox-blue.svg)]() [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)]()

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Other implementations of jthread](#other-implementations-of-jthread)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

<!-- - [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests) -->

## Example usage

```Cpp
#include "nonstd/jthread.hpp"
#include <iostream>

int main(int argc, char **)
{
    int product = 0;
    const int six = 6;
    const int seven = 7;

    {
        nonstd::jthread thr{[&](int x, int y){ product = x * y; }, six, seven };

        // automatically join thread here, making sure it has executed:
    }

    std::cout << "Product of "<< six << " and " << seven << " is " << product << ".\n";
}
```

### Compile and run

```Text
$ g++ -std=c++11 -Wall -I../include/ -o 02-arguments.exe 02-arguments.cpp && 02-arguments.exe
Product of 6 and 7 is 42.
```

## In a nutshell

**jthread lite** is a single-file header-only library to provide [C++20's class jthread](https://en.cppreference.com/w/cpp/thread/jthread) for use with C++11 and later. If available, the standard library is used, unless [configured](#configuration) otherwise.

Currently `nonstd::jthread` does not (yet) support thread cancellation using [`stop_token`](https://en.cppreference.com/w/cpp/thread/stop_token), [`stop_source`](https://en.cppreference.com/w/cpp/thread/stop_source) and [`stop_callback`](https://en.cppreference.com/w/cpp/thread/stop_callback). It also does not support [`std::condition_variable_any`](https://en.cppreference.com/w/cpp/thread/condition_variable_any).

**Features and properties of jthread lite** are ease of installation (single header), freedom of dependencies other than the standard library.

**Limitations of jthread lite** are ... \[*to be summed up*\].

## License

*jthread lite* is distributed under the [Boost Software License](https://github.com/martinmoene/jthread-lite/blob/master/LICENSE.txt).

## Dependencies

*jthread lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*jthread lite* is a single-file header-only library. Put `jthread.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

- [Documentation of `class jthread`](#documentation-of-class-jthread)
- [*jthread lite* implementation status](#jthread-lite-implementation-status)
- [Configuration](#configuration)

### Documentation of class jthread

\[*Envisioned*\] Depending on the compiler and C++ standard used, *jthread lite* behaves less or more like the standard's version. To get an idea of the capabilities of *jthread lite* with your configuration, look at the output of the [tests](test/jthread.t.cpp), issuing `jthread-main.t --pass @`.

For the standard's documentation, see [`class jthread`](https://en.cppreference.com/w/cpp/thread/jthread), which is part of the [C++ thread library](https://en.cppreference.com/w/cpp/thread).

### *jthread lite* implementation status

| Kind               | Type or function             | Notes |
|--------------------|------------------------------|-------|
| **Type**           | **jthread**                  | present, no stop abilities |
| &nbsp;             | **nostopstate_t**            | present |
| &nbsp;             | **stop_token**               | present, no functionality |
| &nbsp;             | **stop_source**              | present, no functionality |
| &nbsp;             | **stop_callback**            | not present, no functionality |
| &nbsp;             | **condition_variable_any**   | not present, no functionality |
| &nbsp;             | &nbsp; | &nbsp; |
| **Objects**        | **nostopstate**              | macro for pre-C++17 (no inline var.) |
| &nbsp;             | &nbsp; | &nbsp; |
| **Utilities**      | **make_stop_callback()**     | not present, deduction guideline workaround |

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *jthread lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/jthread.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define jthread_CPLUSPLUS 201103L`.

### Select `std::jthread` or `nonstd::jthread`

\[*To be implemented*\]

At default, *jthread lite* uses `std::jthread` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use `std::jthread` or jthread lite's `nonstd::jthread` as `nonstd::jthread` via the following macros.

-D<b>jthread\_CONFIG\_SELECT\_JTHREAD</b>=jthread\_SELECT\_JTHREAD\_NONSTD  
Define this to `jthread__CONFIG_SELECT_JTHREAD_STD` to select `std::jthread` as `nonstd::jthread`. Define this to `jthread_SELECT_JTHREAD_NONSTD` to select `nonstd::jthread` as `nonstd::jthread`. Default is undefined, which has the same effect as defining to `jthread_SELECT_JTHREAD_NONSTD` currently (this may change to `jthread_SELECT_JTHREAD_DEFAULT`).

#### Standard selection macro

\-D<b>jthread\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Disable exceptions

-D<b>jthread_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.

## Other implementations of jthread

- [jthread](https://github.com/josuttis/jthread). Nicolai Josuttis. GitHub.

## Notes and references

- [p0660](http://wg21.link/p0660) - Stop Token and Joining Thread. Nicolai Josuttis, Lewis Baker, Billy O’Neal, Herb Sutter, Anthony Williams. 2019.

## Appendix

<a id="a1"></a>
### A.1 Compile-time information

The version of *jthread lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

<a id="a2"></a>
### A.2 Jthread lite test specification

<details>
<summary>click to expand</summary>
<p>

```Text
jthread: Allows to default-construct a jthread
jthread: Allows to create a thread with a callback - no parameters
jthread: Allows to create a thread with a callback - with parameters
jthread: Allows to check if a thread is joinable
jthread: Allows to join a thread
jthread: Allows to detach a thread
jthread: Allows to obtain stop_source - stop_source not-implemented
jthread: Allows to obtain stop_token - stop_token not-implemented
jthread: Allows to request a thread to stop - stop_token not-implemented
jthread: Allows to swap two threads
jthread: Allows to obtain a thread's id[.jthread][.info]
jthread: Allows to obtain a thread's native handle[.jthread][.info]
jthread: Allows to obtain the maximum number of hardware threads[.jthread][.info]
tweak header: Reads tweak header if supported [tweak]
```
