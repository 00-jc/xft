# xft

A freestanding C23 systems library for Linux on x86_64 and aarch64.

`xft` replaces the parts of a C runtime you would normally get from libc: memory
primitives, allocators, containers, I/O, threads, syscalls, program startup. With
implementations that can be linked with `-nostdlib`. It also builds in a hosted
"libc" flavor when you want the same API on top of a normal toolchain (and to get
sanitizers, which need one).

Everything is prefixed `ft_`, uses fixed-width typedefs (`t_u64`, `t_size`,
`t_buffer`, …) from `include/primitives.h`, and returns `t_result` (`OK` / `KO`)
rather than errno.

## Requirements

- CMake >= 3.21
- GCC or Clang with C23 support
- Linux; x86_64 or aarch64 for the freestanding flavor (any arch with `XFT_LIBC=ON`)
- Clang builds with LTO also want `lld` (or pass `-DXFT_LTO=OFF`)

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

That produces `build/libxft.a`. Install with:

```sh
cmake --install build --prefix /usr/local
```

which puts the archive in `<prefix>/lib` and the headers in `<prefix>/include`.

### Options

| Option | Default | Effect |
| --- | --- | --- |
| `XFT_LIBC` | `OFF` | Build against a libc instead of freestanding |
| `XFT_NATIVE` | `ON` | `-march=native -mtune=native` |
| `XFT_LTO` | `ON` | Link-time optimization |
| `XFT_FAST_MATH` | `ON` | `-ffast-math` |
| `XFT_WERROR` | `ON` | `-Werror` |
| `XFT_SANITIZE` | `OFF` | ASan + UBSan (forces `XFT_LIBC=ON`, disables LTO) |
| `XFT_STRICT_ARCH` | `OFF` | Compile only the host's arch backends |
| `XFT_RT` | `ON` | Build the runtime: entry point + `rt` helpers |
| `XFT_BUILD_TESTS` | `OFF` | Build the unit test runner (always sanitized) |
| `XFT_BUILD_FUZZ` | `OFF` | Build the fuzz targets (always sanitized) |
| `XFT_BUILD_BENCH` | `OFF` | Build the benchmarks (never sanitized) |

Two notes on the defaults. `XFT_NATIVE=ON` means the archive is tuned for the
machine that built it, turn it off if you are shipping the binary elsewhere. All
compiler and linker flags are feature-probed, so an unsupported flag is silently
dropped rather than failing the configure; the configure output tells you how many
were accepted:

```
-- xft: flavor=freestanding arch=x86_64 rt=ON nthreads=16 llc=25165824 cc=GNU
-- xft: cflags 14/14 warnings 78/78 accepted
```

By default both the x86_64 and aarch64 backend directories are compiled (their
contents are `#ifdef`-guarded on the target); `XFT_STRICT_ARCH=ON` limits the
source list to the host's.

`XFT_RT=OFF` drops the whole `src/rt` directory: the entry point (`_start`, or
`main` in the libc flavor) and the `ft_get_rt` / `ft_get_kernel_ptrs` helpers.
It also defines `FT_NO_RT` on the target, which guards out their declarations in
`rt.h`, so the archive owns no entry point and you provide your own. The
`t_xft_rt` types stay, since `threads.h` is built on them. The test, fuzz and
bench harnesses are `ft_main` programs, so they need `XFT_RT=ON`; asking for
both is a configure error.

## Using it

The library exports the CMake target `xft::xft`, so the easiest route is
`add_subdirectory`:

```cmake
add_subdirectory(xft)
add_executable(myprog main.c)
target_link_libraries(myprog PRIVATE xft::xft)
```

In the freestanding flavor that target carries the `-ffreestanding -fno-builtin
-fno-stack-protector` compile options and `-nostdlib -static` link options as
INTERFACE properties, so consumers get them automatically. There is no installed
CMake package config, so if you consume the installed archive instead, pass the
flags yourself:

```sh
# freestanding
cc -std=c23 -ffreestanding -fno-builtin -fno-stack-protector -O2 \
   main.c -o myprog -nostdlib -static -lxft

# hosted (library configured with -DXFT_LIBC=ON)
cc -std=c23 -D_GNU_SOURCE -DFT_REQUIRE_LIBC -O2 main.c -o myprog -lxft
```

`FT_REQUIRE_LIBC` and `_GNU_SOURCE` must match how the archive was built — the
headers switch on the former.

### Entry point

`<xft.h>` pulls in every public header. Programs define `ft_main`, not `main`:

```c
#include "xft.h"

void	ft_main(const t_any *__restrict__ const sp)
{
	t_writer	w;
	t_u8		buf[1024];

	(void)sp;
	w = ft_get_fs_writer(ft_fatptr(buf, sizeof(buf)), ft_get_stdout());
	ft_writer_write(&w, ft_fatptr((t_u8 *)"hello\n", 6));
	(void)ft_writer_flush(&w);
	ft_exit(0);
}
```

`sp` is the raw stack pointer the kernel hands to `_start`. Freestanding builds
supply `_start` themselves; hosted builds supply a `main` that synthesizes `sp`
from `argv`. Either way `ft_get_kernel_ptrs(sp)` gives you `argc/argv/envp/auxv`,
and `ft_get_rt(sp)` additionally parses the ELF program headers and the auxv
random bytes. Nothing returns from `ft_main` — call `ft_exit`.

Working programs live in `examples/` (they are not part of the CMake build):

```sh
cc -std=c23 -ffreestanding -fno-builtin -fno-stack-protector -Iinclude -O2 \
   examples/io/str_2_bin.c -o str2bin -nostdlib -static -Lbuild -lxft
./str2bin hi        # 0110100001101001
```

### Allocators

Anything that owns memory takes a `t_allocator`, a vtable plus an opaque
allocator pointer so containers are agnostic about where their bytes come from:

```c
t_gpa		gpa = ft_gpa();
t_allocator	a = ft_gpa_allocator(&gpa);
t_vec		v = ft_vec(a, 16, sizeof(t_u64));

ft_vec_push_back(a, &v, (const t_u8 *)&value, sizeof(t_u64));
ft_vec_destroy(a, &v);
ft_gpa_destroy(&gpa);
```

Four allocators ship: `ft_new_arena_alloc` (bump arena over huge pages, with
checkpoint/rewind), `ft_gpa` (general purpose, 14 size classes over 128 KiB slabs),
`ft_new_page_alloc` (straight to `mmap`), and `ft_reporta` (a GPA that also tracks
allocation counts, reuse, and fragmentation). Note that the free/destroy call must
use the same allocator that produced the buffer, and that containers free only
their own backing storage, elements owning memory must be drained first.

## Modules

| Header | Contents |
| --- | --- |
| `primitives.h` | `t_u8`…`t_u128`, `t_size`, `t_buffer`, `t_result`, `t_span` |
| `mem.h` | `memcpy`/`memset`/`memmove`/`memchr`/`memcmp` with SSE2, AVX2, AVX-512 and NEON paths, plus non-temporal streaming and huge-size variants, prefetch, fences |
| `alloc.h` | Arena, GPA, page and reporting allocators behind one vtable |
| `vec.h`, `str.h`, `map.h` | Growable vector, owned NUL-terminated string, SIMD swiss-table hash map |
| `tokenizer.h` | Vectorized byte-class scanning (`ft_eat_while`, `ft_eat_until`, 8/128/256/512-bit eaters) |
| `hash.h` | XXH3-64 and Murmur3-128 |
| `bmi.h` | popcount, clz/ctz, bswap, rotate, bit packing, next-pow2, branchless select |
| `io.h` | Buffered readers/writers over file descriptors or memory, `mmap`-backed file access |
| `fmt.h` | `ft_fmt_writer` formatting onto a `t_writer` |
| `math.h` | sqrt/rsqrt (with Newton refinement), pow, round, fabs, 3D vector ops |
| `sort.h` | Generic quicksort and a `t_u64` specialization |
| `rng.h` | xoshiro256\*\* |
| `threads.h`, `atomics.h` | `clone`-based threads with TLS setup, join/detach, futex mutexes |
| `syscalls.h` | Raw syscalls (x86_64/aarch64 asm, or libc shims) |
| `rt.h`, `elf.h` | Program startup, auxv/ELF header inspection |
| `perf.h` | `perf_event_open` counters (cycles, instructions, cache, branches, faults), CPU pinning |
| `timing.h` | `ft_rdtsc`, `ft_get_nanos` |
| `tailor.h` | Benchmark harness: calibration, warmup, resampling, per-counter summaries |
| `fuzzer.h` | In-tree fuzzing helpers |
| `hint.h` | `ft_assume`, `ft_pin_invariant`, `ft_hardcrash` |
| `ctype.h`, `cstr.h`, `signals.h`, `macros.h` | Character classes, C-string helpers, signal sets, ANSI colors |

`include/private/` holds internals; they are installed alongside the rest but are
not part of the API.

## Tests, fuzzing, benchmarks

Tests and fuzz targets always link a separately built sanitized, hosted copy of the
library (`libxft-san.a`), so you can keep the main build freestanding and
optimized:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DXFT_BUILD_TESTS=ON -DXFT_BUILD_FUZZ=ON
cmake --build build -j
ctest --test-dir build --output-on-failure       # everything
ctest --test-dir build -L unit                   # unit tests only
ctest --test-dir build -L fuzz                   # fuzz targets only
```

Benchmarks are never sanitized and always link the plain library. They run on the
`tailor` harness, which pins the process to a CPU, calibrates, then reports cycles,
instructions, cache misses and branch misses per operation. `perf_event_open` may
require relaxing `kernel.perf_event_paranoid`.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DXFT_BUILD_BENCH=ON
cmake --build build --target bench -j
cmake --build build --target run-bench
```

There is also an `analyze` target that runs the compiler's static analyzer over the
current flavor's source list:

```sh
cmake --build build --target analyze
```

## Layout

```
include/          public headers (types/ for shared typedefs, private/ for internals)
src/              implementation, one function per file, grouped by module
                  arch backends under x86_64/, aarch64/, libc/, portable/, vec128|256|512/
tests/            unit tests, mirrors src/ layout
fuzz/             fuzz targets for mem, vec, map
bench/            tailor benchmarks for memcpy/memmove/memset, gpa, arena, vec
examples/         standalone programs (not built by CMake)
```

The whole build is driven by the single top-level `CMakeLists.txt`; source lists
are explicit, so adding a file means adding it there.

## Lints

All of this library _is_ and _has to be_ norminette compliant.

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
