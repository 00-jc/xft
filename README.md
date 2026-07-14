# xft

A C library (ex-libft, still norm compliant). Closer to zig's std in spirit, but much less friendly.

## Why?

Fits-all systems are bad, I like my things custom and proper where possible.

## Building against it

See [INSTALL.md](INSTALL.md)

## Requirements

- GNU/Linux
- A GNUC compiler
- Libc (maybe)

## Toolchains

### Main Toolchain

- Zig (with llvm backend)

### Fallback Toolchains

- GCC or Clang with C23 support
- Makefile requires one of each of `llvm-ar`/`gcc-ar` and `llvm-randlib`/`gcc-randlib`

## Libc Linkage

The core library is freestanding on x86_64 and aarch64 by default, libc is linked if `FT_REQUIRE_LIBC` is defined or whenever **any** of the following holds:

- Building the library with sanitizers of any kind (neeeded for the runtime)
- -Dlibc=true is passed to zig build
- Compilation targets an architecture other than x86_64 or aarch64

## Architecture-specific code

Modules that need real per-ISA instructions (not just a GCC/Clang vector-extension builtin,
which is already portable across targets) keep the implementations side by side in `x86_64/`
and `aarch64/` subfolders next to the module - e.g. `src/bmi/x86_64/ft_bitpack.c` and
`src/bmi/aarch64/ft_bitpack.c`.

Each file is internally guarded (`#ifdef __x86_64__` / `#ifdef __aarch64__`) and all variants
are compiled unconditionally into every target; the guards make the non-matching ones empty translation units.
A target-agnostic fallback (either a top-level file in the module or one under `portable/`) covers any other architecture.

This same pattern is used for syscalls (`src/syscalls/x86_64`, `.../aarch64`, `.../libc`),
the mutex backoff (`src/atomics/mutex/ft_mutex_backoff_*.c`),
and runtime startup (`src/rt/x86_64`, `.../aarch64`, `.../libc`).

All test pass for now in `x86_64` native hardware and `aarch64` under qemu.

## Philosophy

- Low latency, correctness, and specialization over general code
- Input validation at initialization, downstream services assume data is well formed and sanitized
- Explicit intent through the type system and arguments
- No state without an owner, no owners in dynamic memory even if it means relying more on the stack
- Clearly defined lifetimes with constructors / destructors
- Heavy inlining and specialization is opt-out, not opt-in

## C++ headers

`cxx/` mirrors `include/` one-to-one (`cxx/vec.hpp` wraps `include/vec.h`, and so on), so every module gets an idiomatic C++ face without touching the C library itself. A few rules hold across the whole tree:

- Every raw C header is pulled in through `extern "C"` (with `restrict`/`_Atomic` shimmed for C++ compatibility), then re-exposed under `xft::<module>` (e.g. `xft::vec`, `xft::mem`).
- Functions keep their C name and exact signature, just namespaced and marked `FT_NOEXCEPT` (a macro in `detail.hpp` that expands to `noexcept` on C++11+ and `throw()` on C++98) - nothing here throws, failures are still reported the same way the C API reports them.
- Structs with real lifetime (`t_vec`, `t_str`, `t_map`, `t_arena`, `t_tailor`, `t_tokenizer`, ...) get a matching class (`Vec<T>`, `Str`, `Map<T>`, `Arena`, `Tailor`, `Tokenizer`, ...) that holds the raw struct as its only member. Each method calls its `::ft_*` C function directly - there's no separate free-function layer duplicating what the class already does. Plain value types with no lifetime of their own (`t_buffer`'s byte-twiddling helpers, `math.h`, `hash.h`, ...) stay free functions, since there's no object to attach them to.
- Containers never hold an allocator as hidden state: `alloc::Allocator` is passed explicitly to every call that needs one, mirroring the C API's own calling convention.
- A few C reserved-in-C++ names are renamed at the class boundary: `new`/`delete`/`goto` become `create`/`erase`/`goto_`.
- Everything is header-only and inline, C++98-compatible (aggregates are value-initialized via `Type()`, no brace-init in mem-initializer lists).
- `cxx/xft.hpp` aggregates every module wrapper, mirroring `include/xft.h`'s module list and order exactly.

> [!WARNING]
> `create()`/`erase()` are not a stand-in for `operator new`/`operator delete`. `new`/`delete` tie construction/destruction to one implicit allocation mechanism (`::operator new` forwarding to `malloc`, throwing `bad_alloc` on failure), while every allocating call in xft takes an explicit allocator argument (arena, gpa, page, ...) chosen per call site, and the library is freestanding by default with no exceptions and no guaranteed `malloc` underneath. `create()`/`erase()` are ordinary functions that construct/tear down the wrapped C struct through whichever allocator you hand them, they never allocate the wrapper object's own storage the way a `new` expression would.

## Runtime

The runtime provided is literally just the stack pointer, additional functionality is provided but not bundled it is user code.

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
- [x] Thread free and exit
- [x] Parse auxv and elf headers for TLS and other mumbo jumbo that enables threads.
- [x] Thread spawning / detaching / joining
- [x] Milestone 1
- [ ] Implement io_uring + threaded io (async / await hooks with lock free stuff)
- [ ] Ditch both zig and make, self host a build system, im sick of both
- [ ] Coalescing Allocator
- [ ] Add more math
