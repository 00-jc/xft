# Installing / Building xft

xft is a static library. There is no system-wide install step; you build
`libxft.a` and link it into your project alongside the `include/` directory.

## Requirements

- Linux
- Norminette >3.3.59 (or latest release), only needed for `zig build lint`
- GNU complexity, only needed for `zig build lint`

## Option 1: Zig (main toolchain)

Requires Zig with the LLVM backend enabled (default).

```sh
zig build core
```

This produces `libxft.a` under `zig-out/lib/`, built freestanding on
x86_64 (see "Libc Linkage" below).

### Other `zig build` steps

| Step             | Description                                    |
|------------------|-------------------------------------------------|
| `core`           | Build the core lib (default install target)      |
| `san`            | Build with sanitizers (ASan/UBSan)               |
| `tsan`           | Build with thread sanitizer                      |
| `nolto`          | Build without LTO                                |
| `test`           | Build and run the sanitized test suite           |
| `fuzz`           | Build and run fuzz targets (sanitized)           |
| `bench`          | Build and run benchmarks                         |
| `analyze`        | Run the clang static analyzer                    |
| `lint`           | Run `complexity` and `norminette`                |

Useful options:

- `-Doptimize=<mode>`:  `Debug`, `ReleaseSafe`, `ReleaseFast`, `ReleaseSmall`
- `-Dlibc=true`: force linking against libc
- `-Dtarget=<triple>`:  cross-compile for a non-default target

## Option 2: Makefile (fallback toolchain)

Requires GCC or Clang with C23 support, plus one of `llvm-ar`/`gcc-ar` and
one of `llvm-ranlib`/`gcc-ranlib`. Optionally glibc or musl.

```sh
make
```

This produces `libxft.a` in the repo root, built with `-march=native`.
Other targets: `make clean`, `make fclean`, `make re`, `make analyze`.

## Libc Linkage

The core library is freestanding on x86_64 by default. Libc is linked if
`FT_REQUIRE_LIBC` is defined, or whenever **any** of the following holds:

- Building the library with sanitizers of any kind (needed for the runtime)
- `-Dlibc=true` is passed to `zig build`
- Compilation targets a non-x86_64 architecture

## Using the library

Link the resulting `libxft.a` and add `include/` to your compiler's include
path, e.g.:

```sh
cc your_program.c -Iinclude -L. -lxft -o your_program
```

## LTO

The library is meant to use lto, so linking against it will have to take that
into account.
