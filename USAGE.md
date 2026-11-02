# Using xft

## Adding the dependency

Add `xft` as a dependency in your `build.zig.zon` and link its artifact:

```zig
const xft = b.dependency("xft", .{
    .target = target,
    .optimize = optimize,
});
exe.root_module.linkLibrary(xft.artifact("xft"));
```

Dependency options use the same names as in [BUILD.md](BUILD.md#options), e.g. `.@"use-libc" = true`. The headers come with the artifact, and on Linux so do `perf` and `tailor`.

In the freestanding flavor, do not link libc, and compile your own sources with `-ffreestanding -fno-builtin -fno-stack-protector`.

In the hosted flavor, threads go through pthreads. The freestanding flavor creates threads with `clone(2)`. See [INSTALL.md](INSTALL.md#linking-the-archives-by-hand) when linking `libxft.a` by hand.

## Writing a program

Include `<xft.h>` and define `xft_main` in place of `main`. It receives the initial stack pointer and must end with `xft_exit_process`:

```c
#include <xft.h>

void
xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;

	kp = xft_get_kernel_ptrs(sp);
	xft_kernel_ptrs_destroy(&kp);
	xft_exit_process(0);
}
```

## Windows

`xft` calls into the system DLLs even in the freestanding flavor, so it depends on the `kernel32`, `shell32`, `bcrypt`, and `api-ms-win-core-synch-l1-2-0` import libraries. The `xft` artifact links them for you. A freestanding Windows executable uses `_start` as its entry point.

## Design

- **Prefixed.** Every public symbol is `xft_`. There are no macro aliases into the global namespace except the weak `memcpy`/`memset` symbols emitted for the compiler's benefit in freestanding builds.
- **Explicit error handling.** Fallible functions return `t_result` (`OK` / `KO`). There is no `errno`, and no hidden global state.
- **Fixed-width, aligned types.** Integer and floating-point typedefs are fixed-width and encode alignment in the name: the plain type has alignment 1 and is safe for unaligned access, the `a` suffix carries natural alignment. Every primitive is `may_alias`.
- **Allocators are values.** Containers take a `t_allocator` by value and call through a vtable. The backend (arena, GPA, page allocator, reporting allocator) is chosen by the caller; nothing allocates behind your back.

## Subsystems

| Header | Contents |
| --- | --- |
| `xft/alloc.h` | Allocator interface; arena, general-purpose, page, and reporting allocators, and mutex-locked variants of the arena, general-purpose, and reporting allocators |
| `xft/atomics.h` | Mutexes, futexes, signals, ring buffers, and atomic types |
| `xft/bmi.h` | Bit manipulation, byte order, SIMD mask primitives |
| `xft/cstr.h` | NUL-terminated string helpers |
| `xft/ctype.h` | ASCII character classification |
| `xft/files.h` | Opening, closing, and describing files |
| `xft/fmt.h` | Formatted output to a writer |
| `xft/fuzzer.h` | Random input pool for fuzz targets |
| `xft/hash.h` | XXH3 and Murmur3 |
| `xft/hint.h` | Runtime invariants and optimizer hints |
| `xft/indexmap.h` | Open-addressing hash map from byte keys to indices |
| `xft/io.h` | Buffered readers and writers, standard handles, file mapping |
| `xft/math.h` | Math functions |
| `xft/mem.h` | `memcpy`, `memmove`, `memset`, `memchr`, `memcmp`, and friends |
| `xft/os.h` | CPU count and other operating system queries |
| `xft/rng.h` | xoshiro256\*\* |
| `xft/rt.h` | Program entry point and runtime |
| `xft/signals.h` | Signal number constants |
| `xft/soa.h` | Structure-of-arrays container |
| `xft/sort.h` | `qsort` variants |
| `xft/str.h` | Growable NUL-terminated byte string |
| `xft/swissmap.h` | SIMD open-addressing hash map from byte keys to pointers |
| `xft/threads.h` | Spawning, joining, detaching threads and general purpose threadpools |
| `xft/timing.h` | Clocks and cycle counters |
| `xft/vec.h` | Untyped growable array |
| `xft/xid.h` | Unicode XID_Start/XID_Continue lookup and tables |

`<xft.h>` includes every header above except `signals.h`. The full API is documented in section 3 man pages under `doc/man3`.
