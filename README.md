```txt
xft

A C library (ex-libft, still norm compliant).

Build (zig):

    zig build core                     # -O3 + LTO
    zig build nolto                    # -O3 - LTO (to inspect disassembly)
    zig build san                      # debug + sanitizers (UBSan)
    zig build tsan                     # thread sanitizer
    zig build test                     # run tests (sanitized)
    zig build bench                    # runs the benchmarks (self-hosted)
    zig build fuzz                     # runs the fuzzers (sanitized, self-hosted)
    zig build analyze                  # runs clang's static analyzer

    zig build -Doptimize=ReleaseFast   # override optimize mode
    zig build -Dcpu=native             # -march=native alternative
    zig build -Dtarget=...             # cross-compile target

Build (make fallback):

    make                               # builds xft.a with the default compiler
    make CC=clang                      # force clang
    make CC=gcc                        # force gcc
    make re                            # full rebuild
    make analyze                       # clang scan-build + gcc -fanalyzer + norminette
    make clean
    make fclean

Requirements:

- Requires GCC or Clang with C23 and C99 support.
- Linux.
- Norminette >3.3.59 (lastest release)
- Libc (this lib is not freestanding).
- Zig requires clang/llvm.
- Makefile requires one of clang or gcc.
- Makefile requires one of each of llvm-ar/gcc-ar and
  llvm-randlib/gcc-randlib to be installed

Implementation details:

- Uses src/tailor/ for the bench target
- Uses src/fuzz/ for the fuzz target
- No allocator is thread safe.
- Functions that can fail return explicit errors as values,
  t_result {OK|KO}, contructor, return 0-initialized
  structs for the sake of avoiding stack spills,
  and allocators return t_buffer{mem:nullptr,len:0} on failure.
- Almost all functions assume non-null pointers and valid data,
  the programmer is responsible for correct usage of the library.
- The library is most likely to crash directly than return an error.
- Any function that allocates memory will ask you for an allocator
  Vtable interface.
- Test/Benches regarding to strlen in gcc might fail,
  gcc's redzoning flag it but works fine in real world
  usage, clang/llvm runtimes pass the sanitized tests fine.

Guarantees:

- All assembly is written as inline `__asm__` in C files and protected
  at compile time. No raw assembly nor hidden/extern code that the compiler
  cannot see.
- All vector and SIMD is done by vector types, not includes
  or 'propietary' logic. Vectors may or may not be portable solely
  based on the compiler and target.
- No partial recovery or automatic cleanup of resources on
  non-fatal failure, the programmer must account for that explicitly.
- All files pass norminette.
- All logic is contained in functions, no macros exist except for
  literals, as per norminette, inlining accross translation units
  is done via lto, no preprocessor or logic in headers magic.

Philosophy:

- Low latency, correctness and specialization over general code.
- Assumes input validation at initialization. 
- Explicit intent through type system and arguments, no state without
  an owner, and no owners in dynamic memory.

Notes:

~500 commits were lost when migrating to codeberg, this
library started around april of 2025. Doesn't really impact
the code bc there were massive rewrites but worth noting.

It has only been tested on x86_64, there might be quirks about
toolchains or flags, but hopefully they should not affect logic
and should be easily tackled.

Code compiles clean for aarch64 at the very least, but cannot be
tested due to lack of supporting hw.

```
