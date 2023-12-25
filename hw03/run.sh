#!/usr/bin/env bash

python3 parser.py in.ll out.cpp && \
clang++-14 \
    -g \
    $(llvm-config-14 --cppflags --ldflags --libs) \
    out.cpp ../hw01/sim.c \
    -I ../hw01/ -I ../hw01/build/_deps/csfml-src/include/ \
    -L ../hw01/build/lib/ \
    -l csfml-graphics -l csfml-system \
    -Wl,-rpath,../hw01/build/lib/ \
    -o build/out && \
./build/out out.ll
