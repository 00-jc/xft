# xft

A freestanding C23 systems library for Linux and Windows.

`xft` implements the subset of libc that a systems program typically depends on: memory primitives, containers, allocators, syscall wrappers, I/O, and formatting. It links with `-nostdlib`. Programs that target it define `xft_main` instead of `main` and never touch the C runtime.

A hosted build (`-DXFT_LIBC=ON`) exposes the same API on a normal toolchain, so the library can be used incrementally and tested against the system libc.

## Design

- **Prefixed.** Every public symbol is `xft_`. There are no macro aliases into the global namespace except the weak `memcpy`/`memset` symbols emitted for the compiler's benefit in freestanding builds.
- **Explicit error handling.** Fallible functions return `t_result` (`OK` / `KO`). There is no `errno`, and no hidden global state.
- **Fixed-width, aligned types.** Integer and floating-point typedefs are fixed-width and encode alignment in the name: the plain type has alignment 1 and is safe for unaligned access, the `a` suffix carries natural alignment. Every primitive is `may_alias`.
- **Allocators are values.** Containers take a `t_allocator` by value and call through a vtable. The backend (arena, GPA, page allocator, reporting allocator) is chosen by the caller; nothing allocates behind your back.
- **No runtime detection.** ISA-specific paths are selected at compile time from target macros. There is no CPUID dispatch and no lazy initialization or IFuncs.

## Requirements

- CMake >= 3.21
- GCC or Clang with C23 support
- Ninja (the supported generator; on Windows it is required, since the Visual Studio generators ignore `CMAKE_C_COMPILER`)

## Platform support

| Platform | Freestanding | `XFT_LIBC` |
| --- | --- | --- |
| Linux x86_64 | yes | yes |
| Linux aarch64 | yes | yes |
| Linux, other arches | no | yes |
| Windows x86_64 | yes* | yes |
| Other OSes | no | no |

## Building

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces `build/libxft.a`. To install:

```sh
cmake --install build --prefix /usr/local
```

### Options

| Option | Default | Effect |
| --- | --- | --- |
| `XFT_LIBC` | `OFF` | Build against a libc instead of freestanding |
| `XFT_ARCH` | `native` | `-march` value (`native`, `x86-64-v3`, `armv8.2-a`, ...); empty for the compiler default. `native` also adds `-mtune=native`; defaults to empty when cross compiling. Set it to a target when shipping binaries |
| `XFT_LTO` | `ON` | Link-time optimization; Clang + LTO wants `lld` |
| `XFT_FAST_MATH` | `ON` | `-ffast-math` |
| `XFT_SANITIZE` | `OFF` | ASan + UBSan; forces `XFT_LIBC=ON`, disables LTO |
| `XFT_STRICT_ARCH` | `OFF` | Compile only the host architecture's backends |
| `XFT_RT` | `ON` | Use the `xft` entry point calling `xft_main`; `OFF` uses libc's entry point and your `main` (forces `XFT_LIBC=ON`) |
| `XFT_BUILD_TESTS` | `OFF` | Unit tests (always sanitized) |
| `XFT_BUILD_FUZZ` | `OFF` | Fuzz targets (always sanitized) |
| `XFT_BUILD_BENCH` | `OFF` | Benchmarks (never sanitized, Linux only) |
| `XFT_BUILD_GENTABLE` | `OFF` | `gentable` table generator |
| `XFT_BOOTSTRAP_XID` | `OFF` | Build without the xid module and regenerate its table (forces `XFT_BUILD_GENTABLE=ON`) |

Warnings are always errors. `Release` builds use `-Wall -Wextra -Werror`; every other build type uses the strict set in `cmake/warnings_strict.cmake`.

### Regenerating the XID table

`src/xid/xft_xidtable.c` is generated from the Unicode [`DerivedCoreProperties.txt`](https://www.unicode.org/Public/UCD/latest/ucd/DerivedCoreProperties.txt) by `gentable`, which links `xft` itself. Put the file in the source root, then bootstrap:

```sh
cmake -S . -B build-xid -DXFT_BOOTSTRAP_XID=ON
cmake --build build-xid
```

This builds `xft` without the xid module and rewrites the table; the next normal build compiles it back in. See [`xft_xid(3)`](doc/man3/xft_xid.3).

## Usage

Link the `xft::xft` target. It carries the freestanding flags for you:

```cmake
add_subdirectory(xft)
target_link_libraries(myprog PRIVATE xft::xft)
```

Include `<xft.h>` and define `xft_main` instead of `main`. It receives the initial stack pointer and must end with `xft_exit`:

```c
#include <xft.h>

void
xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;

	kp = xft_get_kernel_ptrs(sp);
	xft_kernel_ptrs_destroy(&kp);
	xft_exit(0);
}
```

On Windows, `xft` calls into the system DLLs even in the freestanding flavor, so it depends on the `kernel32`, `ntdll`, and `shell32` import libraries. `xft::xft` links them for you; if you link `libxft.lib` by hand, add them yourself.

## Subsystems

| Header | Contents |
| --- | --- |
| `xft_alloc.h` | Allocator interface; arena, general-purpose, page, and reporting allocators |
| `xft_atomics.h` | Mutexes and atomic types |
| `xft_bmi.h` | Bit manipulation, byte order, SIMD mask primitives |
| `xft_cstr.h` | NUL-terminated string helpers |
| `xft_ctype.h` | ASCII character classification |
| `xft_fmt.h` | Formatted output to a writer |
| `xft_fuzzer.h` | Random input pool for fuzz targets |
| `xft_hash.h` | XXH3 and Murmur3 |
| `xft_hint.h` | Runtime invariants and optimizer hints |
| `xft_indexmap.h` | Open-addressing hash map from byte keys to indices |
| `xft_io.h` | Buffered readers and writers, standard handles, file mapping |
| `xft_math.h` | Math functions |
| `xft_mem.h` | `memcpy`, `memmove`, `memset`, `memchr`, `memcmp`, and friends |
| `xft_rng.h` | xoshiro256\*\* |
| `xft_rt.h` | Program entry point and runtime |
| `xft_signals.h` | Signal masks |
| `xft_soa.h` | Structure-of-arrays container |
| `xft_sort.h` | `qsort` variants |
| `xft_str.h` | Growable NUL-terminated byte string |
| `xft_swissmap.h` | SIMD open-addressing hash map from byte keys to pointers |
| `xft_syscalls.h` | System call wrappers |
| `xft_timing.h` | Clocks and cycle counters |
| `xft_vec.h` | Untyped growable array |
| `xft_xid.h` | Unicode XID_Start/XID_Continue lookup and tables |

The full API is documented in section 3 man pages under `doc/man3`.

## Testing

Unit tests and fuzz targets are built with sanitizers and run under CTest:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DXFT_BUILD_TESTS=ON -DXFT_BUILD_FUZZ=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

On Windows, the sanitized binaries load `clang_rt.asan_dynamic-<arch>.dll`, which LLVM ships outside `bin`. Put its directory on `PATH`:

```powershell
$res = & clang -print-resource-dir
$env:PATH = "$res\lib\windows;$env:PATH"
```

## Benchmarks

Benchmarks use the `tailor` harness and are Linux only:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DXFT_BUILD_BENCH=ON
cmake --build build --target run-bench
```

## Warning

This has been in development for over a year (apr 2025, but commits were lost), but it still has rough edges even if it has been used for fairly
nontrivial programs, for any additions or suggestions please refer to [codeberg](https://codeberg.org/00jc/xft)
and open an issue or pull request, any help at all is very appreciated since this has been a solo project from the
start.

## License

Released into the public domain under the [Unlicense](https://unlicense.org/). See `LICENSE` for the full text.
