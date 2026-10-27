# xft

A freestanding C23 systems library for Linux and Windows.

`xft` implements the subset of libc that a systems program typically depends on: memory primitives, containers, allocators, syscall wrappers, I/O, and formatting. It links with `-nostdlib`. Programs that target it define `xft_main` instead of `main` and never touch the C runtime.

A hosted build (`-Duse-libc`) exposes the same API on a normal toolchain, so the library can be used incrementally and tested against the system libc.

## Design

- **Prefixed.** Every public symbol is `xft_`. There are no macro aliases into the global namespace except the weak `memcpy`/`memset` symbols emitted for the compiler's benefit in freestanding builds.
- **Explicit error handling.** Fallible functions return `t_result` (`OK` / `KO`). There is no `errno`, and no hidden global state.
- **Fixed-width, aligned types.** Integer and floating-point typedefs are fixed-width and encode alignment in the name: the plain type has alignment 1 and is safe for unaligned access, the `a` suffix carries natural alignment. Every primitive is `may_alias`.
- **Allocators are values.** Containers take a `t_allocator` by value and call through a vtable. The backend (arena, GPA, page allocator, reporting allocator) is chosen by the caller; nothing allocates behind your back.

## Requirements

- Zig 0.17.0 or later (it ships the Clang used to compile the C sources; no separate toolchain is needed).

## Platform support

| Platform | Freestanding | `-Duse-libc` |
| --- | --- | --- |
| Linux x86_64 | yes | yes |
| Linux aarch64 | yes | yes |
| Linux, other arches | no | yes |
| Windows x86_64 | yes* | yes |
| Other OSes | no | no |

## Building

```sh
zig build -Doptimize=fast
```

This installs into `zig-out/`:

| Path | Contents |
| --- | --- |
| `zig-out/lib/libxft.a` | The library (`xft.lib` on Windows) |
| `zig-out/lib/libxft-perf.a` | `perf`, Linux only |
| `zig-out/lib/libxft-tailor.a` | `tailor`, Linux only |
| `zig-out/include/xft/` | Public headers, including `perf.h` and `tailor.h` on Linux |

Pass `--prefix /usr/local` (or `-p`) to install somewhere else.

The target and CPU come from Zig's standard options. The default is the host with `-Dcpu=native`; set both when shipping binaries:

```sh
zig build -Doptimize=fast -Dtarget=x86_64-linux -Dcpu=x86_64_v3
zig build -Doptimize=fast -Dtarget=x86_64-windows-gnu
```

### Options

| Option | Default | Effect |
| --- | --- | --- |
| `-Doptimize` | `debug` | `debug`, `safe`, `fast`, `small`; `fast` and `safe` also add `-O3` |
| `-Dtarget` | host | Target triple |
| `-Dcpu` | `native` | CPU model and features (`native`, `baseline`, `x86_64_v3`, ...); the ISA paths in `xft` follow it |
| `-Duse-libc` | `false` | Build against a libc instead of freestanding |
| `-Dsanitize` | `false` | UBSan plus stack checks; requires `-Duse-libc`, disables LTO |
| `-Dlto` | `false` | Full link-time optimization |
| `-Dfast-math` | `false` | `-ffast-math` |
| `-Dllc` | `16777216` | Last level cache size in bytes, used to pick the non-temporal thresholds |
| `-Dtests` | `false` | Unit tests (always sanitized) |
| `-Dfuzz` | `false` | Fuzz targets; requires `-Dsanitize -Duse-libc` |
| `-Dbenches` | `false` | Benchmarks; requires `-Doptimize=fast`, Linux only, no `-Dsanitize` |
| `-Dbootstrap` | `false` | Build without the xid module, build `gentable`, and regenerate the xid table; incompatible with `-Dtests` |

Run `zig build -h` for the full list. Warnings are always errors.

Zig ships no AddressSanitizer runtime, so `-Dsanitize` is UBSan only.

### perf and tailor

On Linux, `xft` builds two more libraries on top of `perf_event_open`, compiled with the same flavor (libc, sanitizers, LTO) as `xft` itself:

- **`perf`** (`<xft/perf.h>`): hardware and software performance counter groups, sampling, and CPU pinning.
- **`tailor`** (`<xft/tailor.h>`): the benchmark harness used by `bench/`, built on `perf`.

Zig consumers that link the `xft` artifact get both automatically. When linking the archives by hand, link them before `xft`: `-lxft-tailor -lxft-perf -lxft`. They are not built for Windows.

### Regenerating the XID table

`src/xid/xft_xidtable.c` is generated from the Unicode [`DerivedCoreProperties.txt`](https://www.unicode.org/Public/UCD/latest/ucd/DerivedCoreProperties.txt) by `gentable` in `subprojects/gentable`, which links `xft` itself. Put the file in the source root, then bootstrap:

```sh
zig build -Dbootstrap
```

This builds `xft` without the xid module and rewrites the table through the `xid-table` step; the next normal build compiles it back in. See [`xft_xid(3)`](doc/man3/xft_xid.3).

## Usage

Add `xft` as a dependency in your `build.zig.zon` and link its artifact:

```zig
const xft = b.dependency("xft", .{
    .target = target,
    .optimize = optimize,
});
exe.root_module.linkLibrary(xft.artifact("xft"));
```

Dependency options use the same names as above, e.g. `.@"use-libc" = true`. The headers come with the artifact. In the freestanding flavor, do not link libc, and compile your own sources with `-ffreestanding -fno-builtin -fno-stack-protector`.

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

On Windows, `xft` calls into the system DLLs even in the freestanding flavor, so it depends on the `kernel32`, `shell32`, and `api-ms-win-core-synch-l1-2-0` import libraries. The `xft` artifact links them for you; if you link `xft.lib` by hand, add them yourself. A freestanding Windows executable uses `_start` as its entry point.

## Subsystems

| Header | Contents |
| --- | --- |
| `xft/alloc.h` | Allocator interface; arena, general-purpose, page, and reporting allocators |
| `xft/atomics.h` | Mutexes and atomic types |
| `xft/bmi.h` | Bit manipulation, byte order, SIMD mask primitives |
| `xft/cstr.h` | NUL-terminated string helpers |
| `xft/ctype.h` | ASCII character classification |
| `xft/fmt.h` | Formatted output to a writer |
| `xft/fuzzer.h` | Random input pool for fuzz targets |
| `xft/hash.h` | XXH3 and Murmur3 |
| `xft/hint.h` | Runtime invariants and optimizer hints |
| `xft/indexmap.h` | Open-addressing hash map from byte keys to indices |
| `xft/io.h` | Buffered readers and writers, standard handles, file mapping |
| `xft/math.h` | Math functions |
| `xft/mem.h` | `memcpy`, `memmove`, `memset`, `memchr`, `memcmp`, and friends |
| `xft/rng.h` | xoshiro256\*\* |
| `xft/rt.h` | Program entry point and runtime |
| `xft/signals.h` | Signal masks |
| `xft/soa.h` | Structure-of-arrays container |
| `xft/sort.h` | `qsort` variants |
| `xft/str.h` | Growable NUL-terminated byte string |
| `xft/swissmap.h` | SIMD open-addressing hash map from byte keys to pointers |
| `xft/syscalls.h` | System call wrappers |
| `xft/timing.h` | Clocks and cycle counters |
| `xft/vec.h` | Untyped growable array |
| `xft/xid.h` | Unicode XID_Start/XID_Continue lookup and tables |

The full API is documented in section 3 man pages under `doc/man3`.

## Testing

Unit tests always link a sanitized hosted build of the library (`xft-san`), or the main library if `-Dsanitize` is already on:

```sh
zig build -Dtests test
```

Fuzz targets need the main build sanitized and hosted:

```sh
zig build -Duse-libc -Dsanitize -Dfuzz fuzz
```

## Benchmarks

Benchmarks use the `tailor` harness and are Linux only:

```sh
zig build -Doptimize=fast -Dbenches run-bench
```

`libc_bench` and `stl_bench` link a hosted build (`xft-libc`) to compare against the system libc and the C++ standard library.

## Warning

This has been in development for over a year (apr 2025, but commits were lost), but it still has rough edges even if it has been used for fairly
nontrivial programs, for any additions or suggestions please refer to [codeberg](https://codeberg.org/00jc/xft)
and open an issue or pull request, any help at all is very appreciated since this has been a solo project from the
start.

## License

Released into the public domain under the [Unlicense](https://unlicense.org/). See `LICENSE` for the full text.
