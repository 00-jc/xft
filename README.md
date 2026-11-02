# xft

xft is a freestanding C23 systems library for Linux and Windows. It provides
memory primitives, containers, allocators, system call wrappers, I/O and
formatting. It links without a C library: programs define `xft_main` in place
of `main` and never touch the C runtime. A hosted build (`-Duse-libc`) exposes
the same API on a normal toolchain.

Freestanding builds run on x86_64 and aarch64 Linux and on Windows. Other Linux
architectures need `-Duse-libc`.

Building requires Zig 0.17.0 or later, which ships the Clang used to compile
the sources. GCC is not supported.

    zig build -Doptimize=fast -Dlto=true

This installs the library and headers into `zig-out/`. See `BUILD.md` for
the platform table, targets and options, `INSTALL.md` for what gets installed
and how to link it, and `USAGE.md` for writing programs against it.

The library is documented in `doc/man7/xft.7`, with the full API in the section
3 pages under `doc/man3`.

xft has been in development since April 2025 and has been used for fairly
nontrivial programs, but it has rough edges. It has been a solo project from
the start and any help is very appreciated: for additions or suggestions, open
an issue or pull request on [Codeberg](https://codeberg.org/00jc/xft).

xft is released into the public domain under the Unlicense. See `LICENSE`.
