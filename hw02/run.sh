#!/usr/bin/env bash

clang++-14 -std=c++17 pass.cpp -c -fPIC -I `llvm-config-14 --includedir` -o pass.o
clang++-14 pass.o -fPIC -shared -o libpass.so
clang-14 \
    -c \
    ../hw01/main.c ../hw01/life.c \
    -I ../hw01/ -I ../hw01/sim/ \
    -Xclang -load -Xclang ./libpass.so \
    -flegacy-pass-manager
