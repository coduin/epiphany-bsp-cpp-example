# Epiphany BSP C++ example

A small example of an Epiphany (BSP) program written in C++. The C++ binary size is greatly reduced by using the appropriate flags, as well as overwriting the `new` and `delete` operators.

This example depends on Epiphany BSP, which is included as a Git submodule. Use

    git submodule init
    git submodule update --remote

The program can then be built by issuing 

    make

from the command-line.
