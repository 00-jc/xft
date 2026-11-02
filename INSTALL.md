# Installing xft

```sh
zig build -Doptimize=fast -Dlto=true -Dcpu=native -Dtarget=native
```

This installs into `zig-out/`:

| Path | Contents |
| --- | --- |
| `zig-out/lib/libxft.a` | The library (`xft.lib` on Windows) |
| `zig-out/lib/libxft-perf.a` | `perf`, Linux only |
| `zig-out/lib/libxft-tailor.a` | `tailor`, Linux only |
| `zig-out/include/xft/` | Public headers, including `perf.h` and `tailor.h` on Linux |

Pass `--prefix /usr/local` (or `-p`) to install somewhere else.

See [BUILD.md](BUILD.md) for requirements, targets and options.

## Linking the archives by hand

Zig consumers that link the `xft` artifact get all of this automatically; see [USAGE.md](USAGE.md).

- `perf` and `tailor` go before `xft`: `-lxft-tailor -lxft-perf -lxft`.
- In the hosted flavor on glibc older than 2.34, add `-lpthread`. glibc 2.34 and later and musl need nothing extra. The freestanding flavor creates threads with `clone(2)` and never links pthreads.
- On Windows, add the `kernel32`, `shell32`, `bcrypt` and `api-ms-win-core-synch-l1-2-0` import libraries.
- On 32-bit targets, add compiler-rt, which provides the 64-bit division (`__udivdi3`, `__umoddi3`).
