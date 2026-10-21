# user options, their validation and the settings they imply.
# needs platform.cmake

option(XFT_LIBC "build against a libc instead of freestanding" OFF)
# -march value: native, x86-64-v3, armv8.2-a, ...; empty is the compiler
# default. native is the host, so a cross build defaults to empty
if(CMAKE_CROSSCOMPILING)
  set(XFT_ARCH "" CACHE STRING "-march value, empty for the compiler default")
else()
  set(XFT_ARCH native CACHE STRING "-march value, empty for the compiler default")
endif()
option(XFT_LTO "link time optimization" ON)
option(XFT_FAST_MATH "-ffast-math" ON)
option(XFT_SANITIZE "asan + ubsan build (implies XFT_LIBC, no LTO)" OFF)
option(XFT_STRICT_ARCH "compile only the arch/backend dirs of the host" OFF)
option(XFT_RT "xft runtime entry point; OFF uses the libc one (implies XFT_LIBC)" ON)
option(XFT_BUILD_TESTS "build the unit test runner (always sanitized)" OFF)
option(XFT_BUILD_FUZZ "build the fuzz targets (always sanitized)" OFF)
option(XFT_BUILD_BENCH "build the benchmarks (never sanitized)" OFF)
option(XFT_BUILD_GENTABLE "build the gentable table generator" OFF)
option(XFT_BOOTSTRAP_XID "build xft without xid and regenerate its table" OFF)

if(WIN32 AND NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(
    FATAL_ERROR
    "xft: only clang is supported on Windows (got ${CMAKE_C_COMPILER_ID}); "
    "the Visual Studio generators ignore CMAKE_C_COMPILER, use "
    "-G Ninja -DCMAKE_C_COMPILER=clang (from a fresh build dir)"
  )
endif()

# clang-cl takes cl-style flags and cmake links through lld-link directly,
# so the gnu-style flags and link options used everywhere would not apply
if(WIN32 AND CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
  message(
    FATAL_ERROR
    "xft: clang-cl is not supported, use the gnu-style driver: "
    "-G Ninja -DCMAKE_C_COMPILER=clang (from a fresh build dir)"
  )
endif()

if(XFT_TARGET_ARCH STREQUAL "unknown" AND NOT XFT_LIBC)
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

if(NOT XFT_RT AND NOT XFT_LIBC)
  message(STATUS "xft: XFT_RT=OFF forces XFT_LIBC=ON")
  set(XFT_LIBC ON)
endif()

if(CMAKE_CROSSCOMPILING AND XFT_ARCH STREQUAL "native")
  message(
    FATAL_ERROR
    "xft: XFT_ARCH=native targets the build host, which a cross build is not; "
    "name the target, e.g. -DXFT_ARCH=x86-64-v3 or -DXFT_ARCH=armv8.2-a"
  )
endif()

if(XFT_BOOTSTRAP_XID)
  if(NOT XFT_BUILD_GENTABLE)
    message(STATUS "xft: XFT_BOOTSTRAP_XID forces XFT_BUILD_GENTABLE=ON")
    set(XFT_BUILD_GENTABLE ON)
  endif()
  if(NOT EXISTS ${PROJECT_SOURCE_DIR}/DerivedCoreProperties.txt)
    message(
      FATAL_ERROR
      "xft: XFT_BOOTSTRAP_XID expects DerivedCoreProperties.txt in the source "
      "root; grab it from "
      "https://www.unicode.org/Public/UCD/latest/ucd/DerivedCoreProperties.txt"
    )
  endif()
  if(XFT_BUILD_TESTS)
    message(
      FATAL_ERROR
      "xft: XFT_BOOTSTRAP_XID leaves the xid module out, which the unit "
      "tests need; bootstrap in its own build tree"
    )
  endif()
endif()

if(
  NOT XFT_RT
  AND (XFT_BUILD_TESTS OR XFT_BUILD_FUZZ OR XFT_BUILD_BENCH OR XFT_BUILD_GENTABLE)
)
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
  "xft: flavor=${XFT_FLAVOR} arch=${XFT_TARGET_ARCH} march=${XFT_ARCH} "
  "rt=${XFT_RT} "
  "llc=${XFT_LLC} cc=${CMAKE_C_COMPILER_ID}"
)
