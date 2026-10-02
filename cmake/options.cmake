# user options, their validation and the settings they imply.
# needs platform.cmake

option(XFT_LIBC "build against a libc instead of freestanding" OFF)
option(XFT_NATIVE "-march=native -mtune=native" ON)
option(XFT_LTO "link time optimization" ON)
option(XFT_FAST_MATH "-ffast-math" ON)
option(XFT_SANITIZE "asan + ubsan build (implies XFT_LIBC, no LTO)" OFF)
option(XFT_STRICT_ARCH "compile only the arch/backend dirs of the host" OFF)
option(XFT_RT "build the runtime: entry point + rt helpers" ON)
option(XFT_BUILD_TESTS "build the unit test runner (always sanitized)" OFF)
option(XFT_BUILD_FUZZ "build the fuzz targets (always sanitized)" OFF)
option(XFT_BUILD_BENCH "build the benchmarks (never sanitized)" OFF)

if(WIN32 AND NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(
    FATAL_ERROR
    "xft: only clang is supported on Windows (got ${CMAKE_C_COMPILER_ID}); "
    "the Visual Studio generators ignore CMAKE_C_COMPILER, use "
    "-G Ninja -DCMAKE_C_COMPILER=clang (from a fresh build dir)"
  )
endif()

if(XFT_ARCH STREQUAL "unknown" AND NOT XFT_LIBC)
  message(
    FATAL_ERROR
    "xft: no freestanding backend for ${CMAKE_SYSTEM_PROCESSOR}; "
    "reconfigure with -DXFT_LIBC=ON"
  )
endif()

if(XFT_SANITIZE)
  set(XFT_LTO OFF)
  if(NOT XFT_LIBC)
    message(STATUS "xft: XFT_SANITIZE forces XFT_LIBC=ON")
    set(XFT_LIBC ON)
  endif()
endif()

if(CMAKE_CROSSCOMPILING AND XFT_NATIVE)
  message(STATUS "xft: cross compiling, forcing XFT_NATIVE=OFF")
  set(XFT_NATIVE OFF)
endif()

if(NOT XFT_RT AND (XFT_BUILD_TESTS OR XFT_BUILD_FUZZ OR XFT_BUILD_BENCH))
  message(
    FATAL_ERROR
    "xft: the test/fuzz/bench harnesses are xft_main programs and need the "
    "runtime; reconfigure with -DXFT_RT=ON or drop the harness options"
  )
endif()

if(XFT_BUILD_BENCH AND NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(
    FATAL_ERROR
    "xft: the benchmarks run on tailor/perf, which are linux only"
  )
endif()

# asan on windows refuses the debug crt (/MDd), which cmake picks for Debug;
# the sanitized builds (XFT_SANITIZE, or the xft-san test/fuzz variant) take
# the release dll crt instead
if(XFT_WIN64 AND (XFT_SANITIZE OR XFT_BUILD_TESTS OR XFT_BUILD_FUZZ))
  set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
endif()

if(XFT_LIBC AND XFT_WIN64)
  set(XFT_FLAVOR "win64-libc")
elseif(XFT_LIBC)
  set(XFT_FLAVOR "libc")
elseif(XFT_WIN64)
  set(XFT_FLAVOR "win64")
else()
  set(XFT_FLAVOR "freestanding")
endif()

message(
  STATUS
  "xft: flavor=${XFT_FLAVOR} arch=${XFT_ARCH} rt=${XFT_RT} "
  "llc=${XFT_LLC} cc=${CMAKE_C_COMPILER_ID}"
)
