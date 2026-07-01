# xft

A C library (ex-libft, still norm compliant). Closer to zig's std in spirit, but much less friendly.

# Why?

Started for school, now I don't like libc's defaults and I run perf at least 2 times a day.

## Building against it

See [INSTALL.md](INSTALL.md)

## Requirements

- Linux
- Norminette >3.3.59 (or latest release)
- GNU complexity

## Toolchains

### Main Toolchain

- Zig (with llvm backend)

### Fallback Toolchains

- GCC or Clang with C23 support
- Makefile requires one of each of `llvm-ar`/`gcc-ar` and `llvm-randlib`/`gcc-randlib`
- Optionally, glibc / musl

## Libc Linkage

The core library is freestanding on x86_64 by default,  libc is linked if  `FT_REQUIRE_LIBC` is defined or whenever **any** of the following holds:

- Building the library with sanitizers of any kind (neeeded for the runtime)
- -Dlibc=true is passed to zig build
- Compilation is for non x86_64

## Philosophy

- Low latency, correctness, and specialization over general code
- Input validation at initialization, downstream services assume data is well formed and sanitized
- Explicit intent through the type system and arguments
- No state without an owner, no owners in dynamic memory even if it means relying more on the stack
- Clearly defined lifetimes with constructors / destructors
- Heavy inlining and specialization is opt-out, not opt-in

## TODO

- [x] Implement clock_gettime / get_ns natively to not depend on LIBC (rdtsc)
- [x] Add /usr/include/linux to the include path
- [x] Clean all system includes (freestanding!!)
- [x] Figure out how to cleanly split x86 freestanding mode from libc mode apart from the macro (at a target level)
- [x] Figure out how to separate build.zig into smaller files
- [x] Implement a proper IO interface (readers, writers, ...)
- [x] Implement formatting (no varargs, no implicit behaviour)
- [x] Make benches work and the tailor framework adapt to the new IO model.
- [x] Add a lot more tests and separate them in folders more cleanly (make a single entry point)
- [ ] Make an AOSOA data structure
- [ ] Make my own threads and concurrent primitives
- [ ] Implement something like zig's juicy main to pass to ft_main()
- [ ] Coalescing Allocator
- [ ] Implement io_uring + threaded io (async / await hooks)
- [ ] Add more math
