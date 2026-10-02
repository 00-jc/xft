# xft

A freestanding C23 systems library for Linux and Windows on x86_64 and aarch64.

`xft` replaces the parts of libc you would normally rely on and links with `-nostdlib`.

A hosted `XFT_LIBC=ON` flavor gives the same API on a normal toolchain.

- Everything is prefixed `xft_`
- Typedefs are fixed-width, alignment is encoded in the types
- Returns `t_result` (`OK` / `KO`) rather than errno

## Build

Requires CMake >= 3.21 and GCC or Clang with C23 support. Ninja is the supported generator

On Windows, always pass `-G Ninja` (the Visual Studio generators ignore `CMAKE_C_COMPILER`)

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces `build/libxft.a`. Use `cmake --install build --prefix /usr/local` to install.

| Option | Default | Effect |
| --- | --- | --- |
| `XFT_LIBC` | `OFF` | Build against a libc instead of freestanding |
| `XFT_NATIVE` | `ON` | `-march=native -mtune=native` (turn off if shipping the binary) |
| `XFT_LTO` | `ON` | Link-time optimization (Clang + LTO wants `lld`) |
| `XFT_FAST_MATH` | `ON` | `-ffast-math` |
| `XFT_SANITIZE` | `OFF` | ASan + UBSan (forces `XFT_LIBC=ON`, disables LTO) |
| `XFT_STRICT_ARCH` | `ON` | Compile only the host's arch backends |
| `XFT_RT` | `ON` | Build the runtime: entry point + `rt` helpers |
| `XFT_BUILD_TESTS` | `OFF` | Unit tests (always sanitized) |
| `XFT_BUILD_FUZZ` | `OFF` | Fuzz targets (always sanitized) |
| `XFT_BUILD_BENCH` | `OFF` | Benchmarks (never sanitized) |

Warnings are always errors. `Release` builds use `-Wall -Wextra -Werror`; every other build type uses the strict set in `cmake/warnings_strict.cmake`.

## Usage

Link the `xft::xft` target, which carries the freestanding flags for you:

```cmake
add_subdirectory(xft)
target_link_libraries(myprog PRIVATE xft::xft)
```

Programs include `<xft.h>` and define `xft_main` instead of `main`; it must end with `xft_exit`:

## Tests and benchmarks

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DXFT_BUILD_TESTS=ON -DXFT_BUILD_FUZZ=ON
cmake --build build
ctest --test-dir build --output-on-failure

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DXFT_BUILD_BENCH=ON
cmake --build build --target run-bench
```

Benchmarks use the `tailor` harness (so it's linux-only).

---

# LICENSE

```
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org/>
```
