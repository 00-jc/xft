# xft

A C library (ex-libft, still norm compliant).

## Build (zig)

| Command | Description |
|---------|-------------|
| `zig build core` | `-O3` + LTO |
| `zig build nolto` | `-O3` - LTO (to inspect disassembly) |
| `zig build san` | debug + sanitizers (UBSan) |
| `zig build tsan` | thread sanitizer |
| `zig build test` | run tests (sanitized) |
| `zig build bench` | run the benchmarks (self-hosted) |
| `zig build fuzz` | run the fuzzers (sanitized, self-hosted) |
| `zig build analyze` | run clang's static analyzer |

**Overrides:**

```
zig build -Doptimize=ReleaseFast   # override optimize mode
zig build -Dcpu=native             # -march=native alternative
zig build -Dtarget=...             # cross-compile target
```

## Build (make fallback)

| Command | Description |
|---------|-------------|
| `make` | builds `libxft.a` with the default compiler |
| `make CC=clang` | force clang |
| `make CC=gcc` | force gcc |
| `make re` | full rebuild |
| `make analyze` | clang scan-build + gcc -fanalyzer + norminette |
| `make clean` | remove object files |
| `make fclean` | remove all build artifacts |

## Requirements

- GCC or Clang with C23 and C99 support
- Linux
- Norminette >3.3.59 (latest release)
- Libc (this lib is not freestanding)
- Zig requires clang/llvm
- Makefile requires one of clang or gcc
- Makefile requires one of each of `llvm-ar`/`gcc-ar` and `llvm-randlib`/`gcc-randlib`

## Implementation Details

- Uses `src/tailor/` for the bench target
- Uses `src/fuzz/` for the fuzz target
- No allocator is thread safe
- Functions that can fail return explicit errors as values: `t_result {OK|KO}`; constructors return zero-initialized structs to avoid stack spills; allocators return `t_buffer{mem:nullptr,len:0}` on failure
- Almost all functions assume non-null pointers and valid data; correct usage is the programmer's responsibility.
- Will likely cause SIGSEV/SIGABRT on invalid data than return an error, errors will be returned if the function itself fails, not from the data it takes.
- A function has one and one purpose only and it's either validation, logic or driving others.
- Any function that allocates memory requires an allocator vtable interface
- `strlen` tests/benches may fail under gcc due to redzoning, but work fine in real-world usage; clang/llvm runtimes pass the sanitized tests cleanly

## Guarantees

- All assembly is written as inline `__asm__` in C files and protected at compile time; no raw assembly nor hidden/extern code the compiler cannot see
- All vector and SIMD is done via vector types, not includes or proprietary logic; portability depends solely on the compiler and target
- No partial recovery or automatic cleanup of resources on non-fatal failure; the programmer must account for that explicitly

## Philosophy

- Low latency, correctness, and specialization over general code
- Input validation at initialization
- Explicit intent through the type system and arguments; no state without an owner, no owners in dynamic memory

## Style Rules

See [RULES.md](RULES.md).

## Notes

~500 commits were lost when migrating to codeberg; the library started around April 2025. Doesn't really impact the code since there were massive rewrites, but worth noting.

Only tested on x86_64, there might be quirks around toolchains or flags, but they should not affect logic and should be easily tackled.

Code compiles clean for aarch64, but cannot be tested due to lack of supporting hardware.
