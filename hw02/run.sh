#!/usr/bin/env bash

mkdir -p build && \
clang++-14 -std=c++20 pass.cpp -c -fPIC -I `llvm-config-14 --includedir` -o build/pass.o && \
clang++-14 build/pass.o -fPIC -shared -o build/libpass.so && \
clang-14 \
    -O2 \
    ../hw01/main.c ../hw01/life.c ../hw01/sim.c logger.c \
    -I ../hw01/ -I ../hw01/build/_deps/csfml-src/include/ \
    -L ../hw01/build/lib/ \
    -l csfml-graphics -l csfml-system \
    -Wl,-rpath,../hw01/build/lib/ \
    -Xclang -load -Xclang build/libpass.so \
    -flegacy-pass-manager \
    -o build/pass.out && \
./build/pass.out > build/pass_log.txt && \
clang++-14 -std=c++20 -O2 log_parser.cpp -o build/log_parser.out && \
./build/log_parser.out < build/pass_log.txt > pass.txt
