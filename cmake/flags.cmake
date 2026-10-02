# compile/link flags, the toolchain bits picked for them and the warning set.
# needs options.cmake and platform.cmake

include(CheckCCompilerFlag)

set(XFT_DEFINES_PUBLIC "")
if(XFT_LIBC)
  list(APPEND XFT_DEFINES_PUBLIC XFT_REQUIRE_LIBC)
  if(NOT XFT_WIN64)
    list(APPEND XFT_DEFINES_PUBLIC _GNU_SOURCE)
  endif()
endif()
if(NOT XFT_RT)
  list(APPEND XFT_DEFINES_PUBLIC XFT_NO_RT)
endif()
set(XFT_DEFINES_PRIVATE XFT_LLC=${XFT_LLC})

set(XFT_PROBE_CTX "-Werror")
foreach(_xft_d IN LISTS XFT_DEFINES_PUBLIC XFT_DEFINES_PRIVATE)
  string(APPEND XFT_PROBE_CTX " -D${_xft_d}")
endforeach()

# the cached result of a probe is only valid for the context it ran in (the
# flags accepted before it, the defines), so the context hash is part of the
# cache variable's name: toggling an option probes again instead of reusing
function(_xft_probe_var out prefix flag ctx)
  string(MD5 _hash "${ctx}")
  string(SUBSTRING "${_hash}" 0 12 _hash)
  string(MAKE_C_IDENTIFIER "${prefix}_${flag}_${_hash}" _var)
  set(${out} ${_var} PARENT_SCOPE)
endfunction()

function(xft_probe out ctx)
  set(_ok "${${out}}")
  set(_ctx "${${ctx}}")
  foreach(f IN LISTS ARGN)
    _xft_probe_var(_var XFT_HAS "${f}" "${_ctx}")
    set(CMAKE_REQUIRED_FLAGS "${_ctx}")
    set(CMAKE_REQUIRED_QUIET ON)
    check_c_compiler_flag("${f}" ${_var})
    if(${_var})
      list(APPEND _ok "${f}")
      string(APPEND _ctx " ${f}")
    endif()
  endforeach()
  set(${out} "${_ok}" PARENT_SCOPE)
  set(${ctx} "${_ctx}" PARENT_SCOPE)
endfunction()

function(xft_probe_link out ctx)
  set(_ok "${${out}}")
  set(_ctx "${${ctx}}")
  foreach(f IN LISTS ARGN)
    _xft_probe_var(_var XFT_HASL "${f}" "${_ctx}|${_ok}")
    set(CMAKE_REQUIRED_FLAGS "${_ctx}")
    set(CMAKE_REQUIRED_LINK_OPTIONS ${_ok} ${f})
    set(CMAKE_REQUIRED_QUIET ON)
    check_c_compiler_flag("${f}" ${_var})
    if(${_var})
      list(APPEND _ok "${f}")
      string(APPEND _ctx " ${f}")
    endif()
  endforeach()
  set(${out} "${_ok}" PARENT_SCOPE)
  set(${ctx} "${_ctx}" PARENT_SCOPE)
endfunction()

set(CFLAGS_RAW
  -pipe
  -ffunction-sections
  -fdata-sections
  -finline-functions
  -fvisibility=hidden
  -fcf-protection=full
  -ftrivial-auto-var-init=zero
  -fno-common
  -fstack-clash-protection
  -fno-semantic-interposition
  -fstrict-aliasing
  -g3)

if(XFT_NATIVE)
  list(APPEND CFLAGS_RAW -march=native -mtune=native)
endif()
if(XFT_FAST_MATH)
  list(APPEND CFLAGS_RAW -ffast-math)
endif()

if(XFT_WIN64 AND NOT XFT_LIBC)
  list(REMOVE_ITEM CFLAGS_RAW -fstack-clash-protection)
endif()

set(CFLAGS "")
xft_probe(CFLAGS XFT_PROBE_CTX ${CFLAGS_RAW})

set(CFLAGS_HOSTED_RAW -fstack-protector-strong)
set(CFLAGS_FREESTANDING_RAW -ffreestanding -fno-builtin -fno-stack-protector)

# windows commits the stack behind a guard page, so big frames normally call
# __chkstk / ___chkstk_ms; xft does not provide it, and neither does it
# provide __stack_chk_fail: stack checks only exist in the libc flavor
if(XFT_WIN64)
  list(APPEND CFLAGS_FREESTANDING_RAW -mno-stack-arg-probe)
endif()

set(CFLAGS_STACK_CHECK_RAW -fstack-protector-all -fstack-check)
set(XFT_SAN_FLAGS_RAW
  -fsanitize=address,alignment,undefined
  -fsanitize-recover=null
  -fno-omit-frame-pointer)

set(CFLAGS_HOSTED "")
set(CFLAGS_FREESTANDING "")
set(CFLAGS_STACK_CHECK "")
set(XFT_SAN_FLAGS "")
set(_xft_ctx_h "${XFT_PROBE_CTX}")
set(_xft_ctx_f "${XFT_PROBE_CTX}")
set(_xft_ctx_s "${XFT_PROBE_CTX}")
set(_xft_ctx_a "${XFT_PROBE_CTX}")
xft_probe(CFLAGS_HOSTED _xft_ctx_h ${CFLAGS_HOSTED_RAW})
xft_probe(CFLAGS_FREESTANDING _xft_ctx_f ${CFLAGS_FREESTANDING_RAW})
xft_probe(CFLAGS_STACK_CHECK _xft_ctx_s ${CFLAGS_STACK_CHECK_RAW})
xft_probe_link(XFT_SAN_FLAGS _xft_ctx_a ${XFT_SAN_FLAGS_RAW})

list(LENGTH CFLAGS_RAW _xft_n_cflags_raw)
list(LENGTH CFLAGS _xft_n_cflags)
message(STATUS "xft: cflags ${_xft_n_cflags}/${_xft_n_cflags_raw} accepted")
message(STATUS "xft: harness sanitizers ${XFT_SAN_FLAGS}")
message(STATUS "xft: harness stack checking ${CFLAGS_STACK_CHECK}")

# both set XFT_WARNS
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  include(${CMAKE_CURRENT_LIST_DIR}/warnings_release.cmake)
else()
  include(${CMAKE_CURRENT_LIST_DIR}/warnings_strict.cmake)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  find_program(XFT_AR NAMES llvm-ar ar)
  find_program(XFT_RANLIB NAMES llvm-ranlib ranlib)
else()
  find_program(XFT_AR NAMES gcc-ar ar)
  find_program(XFT_RANLIB NAMES gcc-ranlib ranlib)
endif()
if(XFT_AR)
  set(CMAKE_AR "${XFT_AR}")
  set(CMAKE_C_COMPILER_AR "${XFT_AR}")
endif()
if(XFT_RANLIB)
  set(CMAKE_RANLIB "${XFT_RANLIB}")
  set(CMAKE_C_COMPILER_RANLIB "${XFT_RANLIB}")
endif()

set(XFT_LTO_LINK_OPTIONS "")
if(
  XFT_LTO
  AND CMAKE_C_COMPILER_ID MATCHES "Clang"
  AND NOT CMAKE_EXE_LINKER_FLAGS MATCHES "-fuse-ld="
  AND NOT CMAKE_LINKER_TYPE
)
  include(CheckLinkerFlag)
  check_linker_flag(C "-fuse-ld=lld" XFT_HAS_LLD)
  if(XFT_HAS_LLD)
    set(XFT_LTO_LINK_OPTIONS -fuse-ld=lld)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -fuse-ld=lld")
    message(STATUS "xft: clang + lto: linking with lld")
  else()
    message(
      WARNING
      "xft: clang LTO needs an LTO-aware linker but -fuse-ld=lld does not work; "
      "install lld, pass -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=<linker>, "
      "or reconfigure with -DXFT_LTO=OFF"
    )
  endif()
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT XFT_IPO_OK OUTPUT XFT_IPO_MSG LANGUAGES C)
