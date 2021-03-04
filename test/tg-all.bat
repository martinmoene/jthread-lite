:: g++ - Compile all permutations of C++ std and jthread_view-s:

@echo off
for %%v in ( jthread_CONFIG_SELECT_JTHREAD_STD jthread_CONFIG_SELECT_JTHREAD_NONSTD ) do (
    for %%s in ( c++11 c++14 c++17 c++2a ) do (
        call tg.bat %%s %%v
    )
)
