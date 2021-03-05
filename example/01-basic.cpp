#include "nonstd/jthread.hpp"

#include <iostream>
#include <thread>

int main()
{
    std::cout << std::endl << std::boolalpha;

#if defined(THREAD_STD)
    std::thread thr{[]{ std::cout << "Joinable std::thread" << std::endl; }};
#elif defined(JTHREAD_STD)
    std::jthread thr{[]{ std::cout << "Joinable std::jthread" << std::endl; }};
#else
    nonstd::jthread thr{[]{ std::cout << "Joinable nonstd::thread" << std::endl; }};
#endif

    std::cout << "thr.joinable(): " << thr.joinable() << "\n" << std::endl;
}

// define: THREAD_STD, JTHREAD_STD, none/other
// clang-cl -DJTHREAD_STD -std:c++latest -MTd -EHsc -W3 -I../include/ 01-basic.cpp && 01-basic.exe
// g++ -DJTHREAD_STD -std=c++2a -Wall -I../include/ -o 01-basic.exe 01-basic.cpp && 01-basic.exe
