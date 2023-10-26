#!/usr/bin/env bash

clang++-14 -std=c++17 pass.cpp -c -fPIC -I `llvm-config-14 --includedir` -o pass.o
clang++-14 pass.o -fPIC -shared -o libpass.so
clang-14 \
    ../hw01/main.c ../hw01/life.c ../hw01/sim/sim.c \
    -I ../hw01/ -I ../hw01/sim/ -I ../hw01/build/_deps/csfml-src/include/ \
    -L ../hw01/build/lib/ \
    -l csfml-graphics -l csfml-system -l csfml-window \
    -Xclang -load -Xclang ./libpass.so \
    -flegacy-pass-manager
