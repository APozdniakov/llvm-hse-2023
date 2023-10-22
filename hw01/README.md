# LLVM course 2023

## hw01

Implementation of the [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

### Build

```bash
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=<path-to-clang> -DCMAKE_BUILD_TYPE=Release -G Ninja ..
ninja -j "$(nproc)"
```

### Run

```bash
./hw01
```

### Get LLVM IR

LLVM IR is located in [`life.ll`](./life.ll)
