```
xft

A C library (ex-libft, still norm compliant).

Build:

    make          # -O3 + LTO + march=native
    make base     # no opts
    make noflto   # -O3 + march=native - LTO (to inspect dissasembly)
    make test     # run tests
    make analyze  # static analysis + tests
    make bench    # runs the benchmarks (self-hosted)
    make fuzz     # runs the fuzzers (self-hosted)

    make clean
    make fclean
    make re

Notes:

- Requires GCC or Clang with C23 and C99 support
- Only tested with GCC >14.0 or Clang >20.1
- Linux only
- Targets Norminette >3.3.59
- Uses -march=native by default
- Uses src/tailor/ for the bench target
- Uses src/fuzz/ for the fuzzer
```
