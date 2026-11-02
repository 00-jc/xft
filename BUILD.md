# Building xft

## Requirements

Zig 0.17.0 or later. It ships the Clang used to compile the C sources, so no separate toolchain is needed. GCC is not supported: the SIMD mask code uses Clang's `bool` ext-vectors.

## Platform support

| OS | Arch | Freestanding | `-Duse-libc` |
| --- | --- | --- | --- |
| Linux | x86_64 | yes | yes |
| Linux | aarch64 | yes | yes |
| Linux | aarch64_be, riscv64, loongarch64, s390x, sparc64, mips64, mips64el, powerpc64, powerpc64le | no<sup>1</sup> | yes |
| Linux | x86, arm, armeb, thumb, thumbeb, mips, mipsel, powerpc, riscv32, sparc, hexagon | no<sup>1</sup> | yes<sup>3</sup> |
| Linux | arc, csky, loongarch32 | no<sup>5</sup> | no<sup>5</sup> |
| Linux | m68k | no | no |
| Windows | x86_64 | yes<sup>2</sup> | yes |
| Windows | aarch64 | yes<sup>2</sup> | yes |
| Windows | x86, thumb | yes<sup>2, 3</sup> | yes<sup>3</sup> |
| Windows | others, including riscv64 and arm | no<sup>4</sup> | no<sup>4</sup> |
| Others | any | no | no |

1. Freestanding Linux issues system calls with inline `syscall`/`svc` assembly, which exists for x86_64 and aarch64 only; other architectures go through libc's `syscall(2)`.
2. Freestanding Windows calls the win32 API in the system DLLs; see [USAGE.md](USAGE.md#windows).
3. 32-bit targets, apart from the x32 and n32 ABIs, have no `__int128`, so `t_u128`/`t_i128` and the functions that take them (`xft_murmur3`, `xft_pow_u128`, `xft_maxu128`, `xft_memclz_u128`, `xft_memctz_u128`) are left out. 64-bit division calls compiler-rt (`__udivdi3`, `__umoddi3`), which Zig links into executables; add it when linking the archive by hand.
4. Zig cannot write COFF objects for these architectures (`UnsupportedCoffArchitecture`).
5. The toolchain stops first: arc and csky are experimental backends in LLVM 23, left out of its default builds, and Zig's glibc headers for loongarch32 do not compile.

The x32 ABI of x86_64 and the n32 ABI of mips64 build with `-Duse-libc`.

## Commands

```sh
zig build -Doptimize=fast -Dlto=true
```

The target and CPU come from Zig's standard options. The default is the host with `-Dcpu=native`; set both when shipping binaries:

```sh
zig build -Doptimize=fast -Dlto=true -Dtarget=x86_64-linux -Dcpu=x86_64_v3
zig build -Doptimize=fast -Dlto=true -Dtarget=x86_64-windows-gnu
zig build -Doptimize=fast -Dlto=true -Dtarget=x86-windows-gnu
```

On Linux every build adds `-fstack-clash-protection` where Clang supports it (not on arm, mips or 32-bit powerpc).

See [INSTALL.md](INSTALL.md) for what the build installs and where.

## Options

| Option | Default | Effect |
| --- | --- | --- |
| `-Doptimize` | `debug` | `debug`, `safe`, `fast`, `small`; `fast` and `safe` also add `-O3` |
| `-Dtarget` | host | Target triple |
| `-Dcpu` | `native` | CPU model and features (`native`, `baseline`, `x86_64_v3`, ...); the ISA paths in `xft` follow it |
| `-Duse-libc` | `false` | Build against a libc, not freestanding |
| `-Dsanitize` | `false` | UBSan plus stack checks, without the stack checks on 32-bit x86 and ARM, where Zig rejects them; requires `-Duse-libc`, disables LTO |
| `-Dlto` | `true` | Full link-time optimization |
| `-Dfast-math` | `false` | `-ffast-math` |
| `-Dllc` | `16777216` | Last level cache size in bytes, used to pick the non-temporal thresholds |
| `-Dtests` | `false` | Unit tests (always sanitized) |
| `-Dfuzz` | `false` | Fuzz targets; requires `-Dsanitize -Duse-libc` |
| `-Dbenches` | `false` | Benchmarks; requires `-Doptimize=fast`, Linux only, no `-Dsanitize` |
| `-Dbootstrap` | `false` | Build without the xid module, build `gentable`, and regenerate the xid table; incompatible with `-Dtests` |

Run `zig build -h` for the full list. Warnings are always errors.

Zig ships no AddressSanitizer runtime, so `-Dsanitize` is UBSan only.

## perf and tailor

On Linux, `xft` builds two more libraries on top of `perf_event_open`, compiled with the same flavor (libc, sanitizers, LTO) as `xft` itself. They are built only on Linux.

- **`perf`** (`<xft/perf.h>`): hardware and software performance counter groups, sampling, and CPU pinning.
- **`tailor`** (`<xft/tailor.h>`): the benchmark harness used by `bench/`, built on `perf`. It runs benchmarks in parallel on a thread pool, one worker per physical core, interleaves the samples of the benchmarks it compares, calibrates each one, filters outliers, bootstraps a confidence interval for the median, and keeps every result so runs can be compared side by side. See [`xft_tailor(3)`](doc/man3/xft_tailor.3).

## Regenerating the XID table

`src/xid/xft_xidtable.c` is generated from the Unicode [`DerivedCoreProperties.txt`](https://www.unicode.org/Public/UCD/latest/ucd/DerivedCoreProperties.txt) by `gentable` in `subprojects/gentable`, which links `xft` itself. Put the file in the source root, then bootstrap:

```sh
zig build -Dbootstrap
```

This builds `xft` without the xid module and rewrites the table through the `xid-table` step; the next normal build compiles it back in. See [`xft_xid(3)`](doc/man3/xft_xid.3).

## Testing

The `test` step runs two executables, the second only on freestanding-capable Linux (x86_64 and aarch64):

- `tests`, every unit test, linked against a sanitized hosted build (`xft-san`, or the main library with `-Dsanitize`). Its thread tests exercise pthreads.
- `freestanding_thread_tests`, the thread tests alone, linked against a freestanding build (`xft-freestanding`, or the main library without `-Duse-libc`). It exercises `clone(2)`.

```sh
zig build -Dtests test
```

To run only the freestanding thread tests:

```sh
zig build -Dtests freestanding-thread-tests
```

Tests always build sanitized and hosted, so the target needs a libc: use `aarch64-linux-gnu` or `aarch64-linux-musl`, not `aarch64-linux-none`. On 32-bit x86 and ARM the sanitized build leaves out the stack checks.

Fuzz targets need the main build sanitized and hosted:

```sh
zig build -Duse-libc -Dsanitize -Dfuzz fuzz
```

## Benchmarks

Benchmarks use the `tailor` harness and are Linux only:

```sh
zig build -Doptimize=fast -Dcpu=native -Dtarget=native -Dlto=true -Dbenches run-bench
```

This builds and runs a single `bench` executable. It links a hosted build (`xft-libc`), so the suites can compare `xft` against the system libc, the C++ standard library and Abseil. On a native target it leaves out Zig's compiler-rt, so `strlen`, `memcpy` and the other C library functions resolve to the system libc for all three.

`bench/bench.c` queues every suite and runs them in one `xft_tailor_run`, on one worker per physical core, each pinned to its own CPU. It then prints a block per benchmark, followed by the comparison groups. Each entry of a suite's table names its benchmark function, its name and its group (`nullptr` for none):

```c
{xft_memcpy_test_varied, "xft_memcpy_varied", "memcpy_varied"},
{xft_libc_memcpy_varied, "libc_memcpy_varied", "memcpy_varied"},
```

The benchmarks of one group run together on one worker and take their samples in turns, so every member sees the same clock and the same neighbours, and every group runs at once, each on its own worker.

The comparison lists each group with its first member, the `xft` one, as the baseline and every other member's cycles per call against it:

```
 ≈ map_strings_1m_lookup_hit
 ├─ xft_map_strings_1m_lookup_hit = 1580.772363 cycles per_call (baseline) [526.146172 ns]
 ├─ std_map_strings_1m_lookup_hit = 2018.312141 cycles per_call (1.276788x slower) [659.463086 ns]
 ├─ absl_map_strings_1m_lookup_hit = 1001.102766 cycles per_call (1.579031x faster) [330.830951 ns]
```

The comparison is on cycles because the clock of a loaded multi-core part moves with the load, so the times of two benchmarks that ran beside different neighbours are not comparable. Memory-bound benchmarks slow each other down, so their absolute numbers vary with the load; the ratios within a group hold up, and a small ratio is a tie.

A group runs on whichever worker picks it up, at the same time as the others, so the state benchmarks share in `bench/` is thread-local, or read-only and filled before the run.
