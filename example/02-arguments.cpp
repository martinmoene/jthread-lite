#include "nonstd/jthread.hpp"
#include <iostream>

int main()
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

// clang-cl -std:c++14 -MTd -EHsc -W3 -I../include/ 02-arguments.cpp && 02-arguments.exe
// g++ -std=c++11 -Wall -I../include/ -o 02-arguments.exe 02-arguments.cpp && 02-arguments.exe
