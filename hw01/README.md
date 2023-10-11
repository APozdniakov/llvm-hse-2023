# LLVM course 2023

## hw01

Implementation of the [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

### Build

```bash
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=<path-to-clang> -DCMAKE_BUILD_TYPE=Debug -G Ninja ..
ninja
```

### Run

```bash
./hw01
```

### Get LLVM IR

```bash
llvm-dis CmakeFiles/hw01-ir.dir/main.c.o
```
