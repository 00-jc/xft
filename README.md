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

    zig build -Doptimize=ReleaseFast   # override optimize mode
    zig build -Dcpu=native             # -march=native alternative
    zig build -Dtarget=...             # cross-compile target

The legacy Makefile can be found in `legacy/`, it was stripped of test/bench targets,
but it has static anaalysis for clang and gcc.

Notes:

- Requires GCC or Clang with C23 and C99 support
- Only tested with GCC >14.0 and Clang >20.1
- Linux only
- Targets Norminette >3.3.59
- Uses src/tailor/ for the bench target
- Uses src/fuzz/ for the fuzzer
- Test/Benches regarding to strlen in gcc might fail,
  gcc's sanitizer is too aggressive redzoning, clang
  works fine, zig tests are stricter than clang but pass.
```
