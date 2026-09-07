cmake_minimum_required(VERSION 3.21)
project(xft VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(XFT_LIBC          "build against a libc instead of freestanding"     OFF)
option(XFT_NATIVE        "-march=native -mtune=native"                      ON)
option(XFT_LTO           "link time optimization"                           ON)
option(XFT_FAST_MATH     "-ffast-math"                                      ON)
option(XFT_WERROR        "-Werror"                                          ON)
option(XFT_SANITIZE      "asan + ubsan build (implies XFT_LIBC, no LTO)"    OFF)
option(XFT_STRICT_ARCH   "compile only the arch/backend dirs of the host"   OFF)
option(XFT_RT            "build the runtime: entry point + rt helpers"      ON)
option(XFT_BUILD_TESTS   "build the unit test runner (always sanitized)"    OFF)
option(XFT_BUILD_FUZZ    "build the fuzz targets (always sanitized)"        OFF)
option(XFT_BUILD_BENCH   "build the benchmarks (never sanitized)"           OFF)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
  set(XFT_ARCH x86_64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
  set(XFT_ARCH aarch64)
else()
  set(XFT_ARCH unknown)
endif()

if(XFT_ARCH STREQUAL "unknown" AND NOT XFT_LIBC)
  message(FATAL_ERROR
    "xft: no freestanding backend for ${CMAKE_SYSTEM_PROCESSOR}; "
    "reconfigure with -DXFT_LIBC=ON")
endif()

if(XFT_SANITIZE)
  set(XFT_LTO OFF)
  if(NOT XFT_LIBC)
    message(STATUS "xft: XFT_SANITIZE forces XFT_LIBC=ON")
    set(XFT_LIBC ON)
  endif()
endif()

if(NOT XFT_RT AND (XFT_BUILD_TESTS OR XFT_BUILD_FUZZ OR XFT_BUILD_BENCH))
  message(FATAL_ERROR
    "xft: the test/fuzz/bench harnesses are ft_main programs and need the "
    "runtime; reconfigure with -DXFT_RT=ON or drop the harness options")
endif()

if(XFT_LIBC)
  set(XFT_FLAVOR "libc")
else()
  set(XFT_FLAVOR "freestanding")
endif()

include(ProcessorCount)
ProcessorCount(XFT_NTHREADS)
if(XFT_NTHREADS EQUAL 0)
  set(XFT_NTHREADS 1)
endif()

set(XFT_LLC 0)
find_program(XFT_GETCONF getconf)
if(XFT_GETCONF)
  execute_process(COMMAND ${XFT_GETCONF} LEVEL3_CACHE_SIZE
                  OUTPUT_VARIABLE _llc OUTPUT_STRIP_TRAILING_WHITESPACE
                  ERROR_QUIET)
  if(_llc MATCHES "^[0-9]+$")
    set(XFT_LLC ${_llc})
  endif()
endif()

message(STATUS "xft: flavor=${XFT_FLAVOR} arch=${XFT_ARCH} rt=${XFT_RT} "
               "nthreads=${XFT_NTHREADS} llc=${XFT_LLC} cc=${CMAKE_C_COMPILER_ID}")

set(SRCS_ALLOC
  src/alloc/arena/ft_arena_alloc.c
  src/alloc/arena/ft_arena_alloc_scopes.c
  src/alloc/arena/ft_arena_alloc_utils.c
  src/alloc/arena/ft_arena_vtable.c
  src/alloc/ft_alloc_clone.c
  src/alloc/gpa/ft_gpa.c
  src/alloc/gpa/ft_gpa_alloc.c
  src/alloc/gpa/ft_gpa_free.c
  src/alloc/gpa/ft_gpa_realloc.c
  src/alloc/gpa/ft_gpa_vtable.c
  src/alloc/huge_matcher/ft_huge_matcher.c
  src/alloc/page_allocator/ft_palloc.c
  src/alloc/page_allocator/ft_palloc_vtable.c
  src/alloc/report/ft_report.c
  src/alloc/report/ft_report_alloc.c
  src/alloc/report/ft_report_free.c
  src/alloc/report/ft_report_realloc.c
  src/alloc/report/ft_report_vtable.c)

set(SRCS_ATOMICS
  src/atomics/mutex/ft_mutex_backoff_portable.c
  src/atomics/mutex/ft_mutex_busy.c
  src/atomics/mutex/ft_mutex_fast.c
  src/atomics/mutex/ft_mutex_init.c
  src/atomics/mutex/ft_mutex_lock.c
  src/atomics/mutex/ft_mutex_slow.c
  src/atomics/mutex/ft_mutex_unlock.c)

set(SRCS_BMI
  src/bmi/__hasz.c
  src/bmi/__max.c
  src/bmi/__maxs.c
  src/bmi/__populate.c
  src/bmi/ft_align.c
  src/bmi/ft_bitpack.c
  src/bmi/ft_bswap.c
  src/bmi/ft_get128.c
  src/bmi/ft_get256.c
  src/bmi/ft_get512.c
  src/bmi/ft_memclz.c
  src/bmi/ft_memctz.c
  src/bmi/ft_next_pow2.c
  src/bmi/ft_popcount.c
  src/bmi/ft_rollmask.c
  src/bmi/ft_rotl.c
  src/bmi/ft_tern.c
  src/bmi/ft_to_be_from_be.c
  src/bmi/ft_to_be_from_le.c)

set(SRCS_CONTAINERS
  src/containers/str/ft_str.c
  src/containers/str/ft_str_extend.c
  src/containers/str/ft_str_push_back.c
  src/containers/str/ft_str_remove.c
  src/containers/swissmap/ft_map.c
  src/containers/swissmap/ft_map_delete.c
  src/containers/swissmap/ft_map_insert.c
  src/containers/swissmap/ft_map_insert_unchecked.c
  src/containers/swissmap/ft_map_lookup.c
  src/containers/swissmap/ft_map_rehash.c
  src/containers/tokenizer/ft_eat_u128.c
  src/containers/tokenizer/ft_eat_u256.c
  src/containers/tokenizer/ft_eat_u512.c
  src/containers/tokenizer/ft_eat_u8.c
  src/containers/tokenizer/ft_eat_until.c
  src/containers/tokenizer/ft_eat_while.c
  src/containers/tokenizer/ft_tokenizer.c
  src/containers/vec/ft_vec.c
  src/containers/vec/ft_vec_bytesize.c
  src/containers/vec/ft_vec_extend.c
  src/containers/vec/ft_vec_free.c
  src/containers/vec/ft_vec_get.c
  src/containers/vec/ft_vec_pop.c
  src/containers/vec/ft_vec_push_back.c
  src/containers/vec/ft_vec_remove.c)

set(SRCS_CSTR
  src/cstr/ft_cstr_to_str.c
  src/cstr/ft_strlen.c)

set(SRCS_CTYPE
  src/ctype/ft_isalnum.c
  src/ctype/ft_isalpha.c
  src/ctype/ft_isascii.c
  src/ctype/ft_isdigit.c
  src/ctype/ft_isprint.c
  src/ctype/ft_isspace.c
  src/ctype/ft_isxdigit.c)

set(SRCS_FMT
  src/fmt/fmt.c
  src/fmt/ft_fmt_handle_double.c
  src/fmt/ft_fmt_handle_hex.c
  src/fmt/ft_fmt_handle_signed.c
  src/fmt/ft_fmt_handle_slice.c
  src/fmt/ft_fmt_handle_unsigned.c)

set(SRCS_FUZZER
  src/fuzzer/ft_fuzzer.c
  src/fuzzer/ft_fuzzer_get_rand.c
  src/fuzzer/ft_fuzzer_initrand.c)

set(SRCS_HASH
  src/hash/murmur3/ft_murmur3.c
  src/hash/murmur3/ft_murmur3_tail.c
  src/hash/murmur3/ft_murmur_helpers.c
  src/hash/xxh3/ft_xxh3.c
  src/hash/xxh3/ft_xxh3_avalanche.c
  src/hash/xxh3/ft_xxh3_finalizers.c
  src/hash/xxh3/ft_xxh3_large_sizes.c
  src/hash/xxh3/ft_xxh3_medium_sizes.c
  src/hash/xxh3/ft_xxh3_mul128_fold64.c
  src/hash/xxh3/ft_xxh3_rrmxmx.c
  src/hash/xxh3/ft_xxh3_secret.c
  src/hash/xxh3/ft_xxh3_small_sizes.c
  src/hash/xxh3/ft_xxh3_xorshift.c)

set(SRCS_HINT
  src/hint/ft_assume.c
  src/hint/ft_hardcrash.c
  src/hint/ft_pin_invariant.c)

set(SRCS_IO
  src/io/blocking_fd/ft_drain.c
  src/io/blocking_fd/ft_fill.c
  src/io/blocking_fd/ft_flush.c
  src/io/blocking_fd/ft_vtable.c
  src/io/ft_get_fixed_fd.c
  src/io/ft_map_file.c
  src/io/ft_reader_read.c
  src/io/ft_writer_write.c
  src/io/raw_buffer/ft_drain.c
  src/io/raw_buffer/ft_fill.c
  src/io/raw_buffer/ft_flush.c
  src/io/raw_buffer/ft_vtable.c)

set(SRCS_MATH
  src/math/3d/ft_3dadd.c
  src/math/3d/ft_3dcross.c
  src/math/3d/ft_3ddiv.c
  src/math/3d/ft_3ddot.c
  src/math/3d/ft_3dmul.c
  src/math/3d/ft_3dnorm.c
  src/math/3d/ft_3dsub.c
  src/math/3d/ft_3dunit.c
  src/math/ft_drsqrt_xn.c
  src/math/ft_fabs.c
  src/math/ft_pow.c
  src/math/ft_pow_signed.c
  src/math/ft_q_sqrt.c
  src/math/ft_round.c
  src/math/ft_rsqrt.c
  src/math/ft_sqrt.c
  src/math/ft_sqrt_xn.c)

set(SRCS_MEM
  src/mem/arch/ft_memchr.c
  src/mem/arch/ft_memcmp.c
  src/mem/arch/ft_memcpy.c
  src/mem/arch/ft_memmove.c
  src/mem/arch/ft_memset.c
  src/mem/ft_align.c
  src/mem/ft_bzero.c
  src/mem/ft_fatptr.c
  src/mem/ft_fences.c
  src/mem/ft_ldfence.c
  src/mem/ft_membroadcast.c
  src/mem/ft_memtake.c
  src/mem/ft_movs.c
  src/mem/ft_overlap.c
  src/mem/ft_prefetch_intrin.c
  src/mem/ft_prefetch_noop.c
  src/mem/ft_stfence.c
  src/mem/hugebranches/ft_memcpy_huge.c
  src/mem/hugebranches/ft_memmove_huge.c
  src/mem/hugebranches/ft_memset_huge.c
  src/mem/portable/ft_memcpy.c
  src/mem/portable/ft_memset.c
  src/mem/streaming/ft_memcpy_streaming.c
  src/mem/streaming/ft_memset_streaming.c
  src/mem/vec128/ft_memchr.c
  src/mem/vec128/ft_memcmp.c
  src/mem/vec128/ft_memcpy.c
  src/mem/vec128/ft_memset.c
  src/mem/vec256/ft_memchr_vec256.c
  src/mem/vec256/ft_memcmp_vec256.c
  src/mem/vec256/ft_memcpy_vec256.c
  src/mem/vec256/ft_memset_vec256.c
  src/mem/vec512/ft_memchr_vec512.c
  src/mem/vec512/ft_memcmp_vec512.c
  src/mem/vec512/ft_memcpy_vec512.c
  src/mem/vec512/ft_memset_vec512.c)

set(SRCS_PERF
  src/perf/ft_bind_process_to_cpu.c
  src/perf/ft_get_flag_groups.c
  src/perf/ft_perf_counter_interface.c
  src/perf/ft_perf_create_counters.c
  src/perf/ft_perf_destroy_counters.c
  src/perf/ft_perf_sampling.c)

set(SRCS_RNG src/rng/ft_xoshiro256ss.c)

set(SRCS_RT
  src/rt/ft_get_auxv_size.c
  src/rt/ft_get_envp_size.c
  src/rt/ft_get_kernel_ptrs.c
  src/rt/ft_get_rt.c
  src/rt/ft_get_thread_info.c)

set(SRCS_SIGNALS src/signals/ft_sigfillset.c)

set(SRCS_SORT
  src/sort/ft_qsort.c
  src/sort/ft_qsort_u64s.c)

# the syscall backends themselves are flavor-specific and live in
# SRCS_FREESTANDING_* / SRCS_LIBC; this is the arch-neutral remainder.
set(SRCS_SYSCALLS src/syscalls/ft_map_failed.c)

set(SRCS_TAILOR
  src/tailor/ft_tailor_bytes.c
  src/tailor/ft_tailor_calibration.c
  src/tailor/ft_tailor_fuzz.c
  src/tailor/ft_tailor_get_rand_buffer.c
  src/tailor/ft_tailor_get_random_num.c
  src/tailor/ft_tailor_getcount.c
  src/tailor/ft_tailor_new.c
  src/tailor/ft_tailor_resample.c
  src/tailor/ft_tailor_run.c
  src/tailor/ft_tailor_summary.c
  src/tailor/ft_tailor_top.c)

set(SRCS_THREADS
  src/threads/ft_get_cpu_count.c
  src/threads/ft_thread.c
  src/threads/ft_thread_clone.c
  src/threads/ft_thread_detach.c
  src/threads/ft_thread_join.c
  src/threads/ft_thread_settls_generic.c
  src/threads/ft_thread_settls_i386.c
  src/threads/ft_thread_tls_variant_i.c
  src/threads/ft_thread_tls_variant_ii.c)

set(SRCS_TIME
  src/time/ft_get_nanos.c
  src/time/ft_rdtsc.c)

set(MODULES ALLOC ATOMICS BMI CONTAINERS CSTR CTYPE FMT FUZZER HASH HINT IO
            MATH MEM PERF RNG RT SIGNALS SORT SYSCALLS TAILOR THREADS TIME)

if(NOT XFT_RT)
  list(REMOVE_ITEM MODULES RT)
endif()

set(SRCS_ARCH_x86_64
  src/atomics/mutex/ft_mutex_backoff_x86_64.c
  src/bmi/x86_64/ft_bitpack.c
  src/bmi/x86_64/ft_bswap.c
  src/bmi/x86_64/ft_memclz.c
  src/bmi/x86_64/ft_memctz.c
  src/bmi/x86_64/ft_popcount.c)

set(SRCS_ARCH_aarch64
  src/atomics/mutex/ft_mutex_backoff_aarch64.c
  src/bmi/aarch64/ft_bitpack.c
  src/bmi/aarch64/ft_bswap.c
  src/bmi/aarch64/ft_memclz.c
  src/bmi/aarch64/ft_memctz.c
  src/bmi/aarch64/ft_popcount_neon.c)

# the process entry point (_start, or main in the libc flavor); dropped
# wholesale when XFT_RT=OFF, which also defines FT_NO_RT for the headers.
set(SRCS_RT_ENTRY_x86_64  src/rt/x86_64/ft_rt.c)
set(SRCS_RT_ENTRY_aarch64 src/rt/aarch64/ft_rt.c)
set(SRCS_RT_ENTRY_libc    src/rt/libc/ft_rt.c)

set(SRCS_FREESTANDING_x86_64
  src/threads/x86_64/ft_thread_free_exit.c
  src/syscalls/x86_64/ft_clock_gettime.c
  src/syscalls/x86_64/ft_clone.c
  src/syscalls/x86_64/ft_close.c
  src/syscalls/x86_64/ft_execve.c
  src/syscalls/x86_64/ft_exit.c
  src/syscalls/x86_64/ft_fmap.c
  src/syscalls/x86_64/ft_fork.c
  src/syscalls/x86_64/ft_futex.c
  src/syscalls/x86_64/ft_getpid.c
  src/syscalls/x86_64/ft_ioctl.c
  src/syscalls/x86_64/ft_lockf.c
  src/syscalls/x86_64/ft_mkdir.c
  src/syscalls/x86_64/ft_mmap.c
  src/syscalls/x86_64/ft_mprotect.c
  src/syscalls/x86_64/ft_mremap.c
  src/syscalls/x86_64/ft_open.c
  src/syscalls/x86_64/ft_perf_events.c
  src/syscalls/x86_64/ft_read.c
  src/syscalls/x86_64/ft_sched_getaffinity.c
  src/syscalls/x86_64/ft_sched_setaffinity.c
  src/syscalls/x86_64/ft_set_tid_address.c
  src/syscalls/x86_64/ft_sigprocmask.c
  src/syscalls/x86_64/ft_stat.c
  src/syscalls/x86_64/ft_wait4.c
  src/syscalls/x86_64/ft_write.c
  src/syscalls/x86_64/ft_writev.c)

set(SRCS_FREESTANDING_aarch64
  src/threads/aarch64/ft_thread_free_exit.c
  src/syscalls/aarch64/ft_clock_gettime.c
  src/syscalls/aarch64/ft_clone.c
  src/syscalls/aarch64/ft_close.c
  src/syscalls/aarch64/ft_execve.c
  src/syscalls/aarch64/ft_exit.c
  src/syscalls/aarch64/ft_fmap.c
  src/syscalls/aarch64/ft_fork.c
  src/syscalls/aarch64/ft_futex.c
  src/syscalls/aarch64/ft_getpid.c
  src/syscalls/aarch64/ft_ioctl.c
  src/syscalls/aarch64/ft_lockf.c
  src/syscalls/aarch64/ft_mkdir.c
  src/syscalls/aarch64/ft_mmap.c
  src/syscalls/aarch64/ft_mprotect.c
  src/syscalls/aarch64/ft_mremap.c
  src/syscalls/aarch64/ft_open.c
  src/syscalls/aarch64/ft_perf_events.c
  src/syscalls/aarch64/ft_read.c
  src/syscalls/aarch64/ft_sched_getaffinity.c
  src/syscalls/aarch64/ft_sched_setaffinity.c
  src/syscalls/aarch64/ft_set_tid_address.c
  src/syscalls/aarch64/ft_sigprocmask.c
  src/syscalls/aarch64/ft_stat.c
  src/syscalls/aarch64/ft_syscall6.c
  src/syscalls/aarch64/ft_wait4.c
  src/syscalls/aarch64/ft_write.c
  src/syscalls/aarch64/ft_writev.c)

set(SRCS_LIBC
  src/threads/libc/ft_thread_free_exit.c
  src/syscalls/libc/ft_clock_gettime.c
  src/syscalls/libc/ft_clone.c
  src/syscalls/libc/ft_close.c
  src/syscalls/libc/ft_execve.c
  src/syscalls/libc/ft_exit.c
  src/syscalls/libc/ft_fmap.c
  src/syscalls/libc/ft_fork.c
  src/syscalls/libc/ft_futex.c
  src/syscalls/libc/ft_getpid.c
  src/syscalls/libc/ft_ioctl.c
  src/syscalls/libc/ft_lockf.c
  src/syscalls/libc/ft_mkdir.c
  src/syscalls/libc/ft_mmap.c
  src/syscalls/libc/ft_mprotect.c
  src/syscalls/libc/ft_mremap.c
  src/syscalls/libc/ft_open.c
  src/syscalls/libc/ft_perf_events.c
  src/syscalls/libc/ft_read.c
  src/syscalls/libc/ft_sched_getaffinity.c
  src/syscalls/libc/ft_sched_setaffinity.c
  src/syscalls/libc/ft_set_tid_address.c
  src/syscalls/libc/ft_sigprocmask.c
  src/syscalls/libc/ft_stat.c
  src/syscalls/libc/ft_wait4.c
  src/syscalls/libc/ft_write.c
  src/syscalls/libc/ft_writev.c)

if(XFT_STRICT_ARCH)
  set(XFT_BACKEND_ARCHS ${XFT_ARCH})
else()
  set(XFT_BACKEND_ARCHS x86_64 aarch64)
endif()

function(xft_srcs out libc)
  set(_s "")
  foreach(m IN LISTS MODULES)
    list(APPEND _s ${SRCS_${m}})
  endforeach()
  foreach(a IN LISTS XFT_BACKEND_ARCHS)
    list(APPEND _s ${SRCS_ARCH_${a}})
  endforeach()
  if(libc)
    list(APPEND _s ${SRCS_LIBC})
    if(XFT_RT)
      list(APPEND _s ${SRCS_RT_ENTRY_libc})
    endif()
  else()
    foreach(a IN LISTS XFT_BACKEND_ARCHS)
      list(APPEND _s ${SRCS_FREESTANDING_${a}})
      if(XFT_RT)
        list(APPEND _s ${SRCS_RT_ENTRY_${a}})
      endif()
    endforeach()
  endif()
  set(${out} "${_s}" PARENT_SCOPE)
endfunction()

xft_srcs(SRCS ${XFT_LIBC})

set(XFT_DEFINES_PUBLIC "")
if(XFT_LIBC)
  list(APPEND XFT_DEFINES_PUBLIC FT_REQUIRE_LIBC _GNU_SOURCE)
endif()
if(NOT XFT_RT)
  list(APPEND XFT_DEFINES_PUBLIC FT_NO_RT)
endif()
set(XFT_DEFINES_PRIVATE FT_NTHREADS=${XFT_NTHREADS} FT_LLC=${XFT_LLC})

include(CheckCCompilerFlag)

set(XFT_PROBE_CTX "-Werror")
foreach(d IN LISTS XFT_DEFINES_PUBLIC XFT_DEFINES_PRIVATE)
  string(APPEND XFT_PROBE_CTX " -D${d}")
endforeach()

function(xft_probe out ctx)
  set(_ok "${${out}}")
  set(_ctx "${${ctx}}")
  foreach(f IN LISTS ARGN)
    string(MAKE_C_IDENTIFIER "XFT_HAS_${f}" _var)
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
    string(MAKE_C_IDENTIFIER "XFT_HASL_${f}" _var)
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
  -g3)

if(XFT_NATIVE)
  list(APPEND CFLAGS_RAW -march=native -mtune=native)
endif()
if(XFT_FAST_MATH)
  list(APPEND CFLAGS_RAW -ffast-math)
endif()

set(CFLAGS "")
xft_probe(CFLAGS XFT_PROBE_CTX ${CFLAGS_RAW})

set(CFLAGS_HOSTED_RAW      -fstack-protector-strong)
set(CFLAGS_FREESTANDING_RAW -ffreestanding -fno-builtin -fno-stack-protector)

set(CFLAGS_STACK_CHECK_RAW -fstack-protector-all -fstack-check)
set(XFT_SAN_FLAGS_RAW      -fsanitize=address,alignment,undefined
                           -fsanitize-recover=null -fno-omit-frame-pointer)

set(CFLAGS_HOSTED "")
set(CFLAGS_FREESTANDING "")
set(CFLAGS_STACK_CHECK "")
set(XFT_SAN_FLAGS "")
set(_ctx_h "${XFT_PROBE_CTX}")
set(_ctx_f "${XFT_PROBE_CTX}")
set(_ctx_s "${XFT_PROBE_CTX}")
set(_ctx_a "${XFT_PROBE_CTX}")
xft_probe(CFLAGS_HOSTED       _ctx_h ${CFLAGS_HOSTED_RAW})
xft_probe(CFLAGS_FREESTANDING _ctx_f ${CFLAGS_FREESTANDING_RAW})
xft_probe(CFLAGS_STACK_CHECK  _ctx_s ${CFLAGS_STACK_CHECK_RAW})
xft_probe_link(XFT_SAN_FLAGS  _ctx_a ${XFT_SAN_FLAGS_RAW})

set(WARNS_COMMON
  -Wall -Wextra -Wpedantic
  -fstrict-aliasing -Wstrict-aliasing
  -Wshadow
  -Waddress
  -Wattributes
  -Wredundant-decls
  -Wstrict-prototypes
  -Wmissing-prototypes
  -Wold-style-definition
  -Wnull-dereference
  -Wundef
  -Wformat-security
  -Wformat=2
  -Wformat-nonliteral
  -Wwrite-strings
  -Wuninitialized
  -Wpointer-arith
  -Wunused
  -Wtautological-compare
  -Wvla
  -Wignored-qualifiers
  -Wnonnull
  -Winfinite-recursion
  -Wimplicit
  -Wimplicit-fallthrough
  -Wmissing-braces
  -Wmissing-include-dirs
  -Wparentheses
  -Wshift-negative-value
  -Wmisleading-indentation
  -Wfloat-equal
  -Wdangling-else
  -Wmissing-noreturn
  -Wchar-subscripts
  -Wsequence-point
  -Wbool-operation
  -Wunreachable-code
  -Wformat-overflow
  -Wformat-truncation
  -Wcast-function-type)
  # -Wdouble-promotion

set(WARNS_CLANG
  -Wbitwise-instead-of-logical
  -Wnull-pointer-arithmetic
  -Wcast-function-type-strict
  -Wambiguous-ellipsis
  -Wambiguous-macro
  -Wassume
  -Wpessimizing-move
  -Wgnu-union-cast
  -Wlanguage-extension-token
  -Wgnu-statement-expression-from-macro-expansion
  -Wbounds-safety-counted-by-elt-type-unknown-size
  -Wcast-function-type-mismatch
  -Wc99-compat
  -Wbool-conversions
  -Wbitfield-enum-conversion
  -Warray-bounds-pointer-arithmetic
  -Wloop-analysis
  -Wcomma
  -Wover-aligned
  -Wconditional-uninitialized
  -Wimplicit-float-conversion
  -Wimplicit-int-conversion
  -Wshorten-64-to-32
  -Wstring-concatenation
  -Wunused-but-set-parameter
  -Wsizeof-array-div
  -Wtautological-constant-in-range-compare
  -Wno-extra-semi-stmt
  -Wthread-safety
  -Wdangling)
  # -Wunsafe-buffer-usage

set(WARNS_GCC
  -Wshift-overflow
  -Wunused-but-set-parameter
  -Wstrict-overflow=5
  -Wmissing-attributes
  -Wmismatched-dealloc
  -Wtrivial-auto-var-init
  -Wuse-after-free=3
  -Wuseless-cast
  --strict-flex-arrays=3
  -Wsuggest-attribute=pure
  -Wsuggest-attribute=const
  -Wsuggest-attribute=noreturn
  -Wsuggest-attribute=malloc
  -Wsuggest-attribute=format
  -Wsuggest-attribute=cold
  -Walloc-size
  -Walloca
  -Warith-conversion
  -Warray-bounds=2
  -Warray-compare
  -Warray-parameter
  -Wattribute-alias=2
  -Wduplicated-branches
  -Wduplicated-cond
  -Wzero-length-bounds
  -Wunsafe-loop-optimizations
  -Wtype-limits
  -Wdangling-pointer
  -Wsizeof-pointer-memaccess
  -Wpacked
  -Wrestrict
  -Winit-self
  -Wlogical-op
  -Wstringop-overflow=4
  -Wstringop-truncation)

if(XFT_LIBC)
  list(INSERT WARNS_GCC 0 -Whardened)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(WARNS_RAW ${WARNS_COMMON} ${WARNS_CLANG})
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(WARNS_RAW ${WARNS_COMMON} ${WARNS_GCC})
else()
  message(WARNING "xft: unknown compiler ${CMAKE_C_COMPILER_ID}, using common warnings only")
  set(WARNS_RAW ${WARNS_COMMON})
endif()

set(WARNS "")
xft_probe(WARNS XFT_PROBE_CTX ${WARNS_RAW})

list(LENGTH CFLAGS_RAW _n_cflags_raw)
list(LENGTH CFLAGS     _n_cflags)
list(LENGTH WARNS_RAW  _n_warns_raw)
list(LENGTH WARNS      _n_warns)
message(STATUS "xft: cflags ${_n_cflags}/${_n_cflags_raw} warnings ${_n_warns}/${_n_warns_raw} accepted")

message(STATUS "xft: harness sanitizers ${XFT_SAN_FLAGS}")
message(STATUS "xft: harness stack checking ${CFLAGS_STACK_CHECK}")

if(XFT_WERROR)
  list(APPEND WARNS -Werror)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  find_program(XFT_AR     NAMES llvm-ar ar)
  find_program(XFT_RANLIB NAMES llvm-ranlib ranlib)
else()
  find_program(XFT_AR     NAMES gcc-ar ar)
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
if(XFT_LTO AND CMAKE_C_COMPILER_ID MATCHES "Clang"
   AND NOT CMAKE_EXE_LINKER_FLAGS MATCHES "-fuse-ld=" AND NOT CMAKE_LINKER_TYPE)
  include(CheckLinkerFlag)
  check_linker_flag(C "-fuse-ld=lld" XFT_HAS_LLD)
  if(XFT_HAS_LLD)
    set(XFT_LTO_LINK_OPTIONS -fuse-ld=lld)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -fuse-ld=lld")
    message(STATUS "xft: clang + lto: linking with lld")
  else()
    message(WARNING
      "xft: clang LTO needs an LTO-aware linker but -fuse-ld=lld does not work; "
      "install lld, pass -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=<linker>, "
      "or reconfigure with -DXFT_LTO=OFF")
  endif()
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT XFT_IPO_OK OUTPUT XFT_IPO_MSG LANGUAGES C)

function(xft_add_lib name)
  cmake_parse_arguments(L "LIBC;SANITIZE;LTO" "" "" ${ARGN})
  if(L_SANITIZE)
    set(L_LIBC ON)
    set(L_LTO OFF)
  endif()

  xft_srcs(_srcs ${L_LIBC})
  add_library(${name} STATIC ${_srcs})

  set_target_properties(${name} PROPERTIES
    OUTPUT_NAME ${name}
    PREFIX "lib"
    C_VISIBILITY_PRESET hidden
    POSITION_INDEPENDENT_CODE OFF)

  target_include_directories(${name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

  target_compile_definitions(${name} PRIVATE ${XFT_DEFINES_PRIVATE})
  target_compile_options(${name} PRIVATE
    ${CFLAGS} ${WARNS} $<$<CONFIG:Release,RelWithDebInfo,>:-O3>)

  if(NOT XFT_RT)
    target_compile_definitions(${name} PUBLIC FT_NO_RT)
  endif()

  if(L_LIBC)
    target_compile_definitions(${name} PUBLIC FT_REQUIRE_LIBC _GNU_SOURCE)
    target_compile_options(${name} PRIVATE ${CFLAGS_HOSTED})
  else()
    target_compile_options(${name} PRIVATE ${CFLAGS_FREESTANDING})
    target_compile_options(${name} INTERFACE ${CFLAGS_FREESTANDING})
    target_link_options(${name} INTERFACE -nostdlib -static)
  endif()

  if(L_SANITIZE)
    target_compile_options(${name} PUBLIC ${XFT_SAN_FLAGS} ${CFLAGS_STACK_CHECK})
    target_link_options(${name} PUBLIC ${XFT_SAN_FLAGS})
  endif()

  if(L_LTO)
    if(XFT_IPO_OK)
      set_property(TARGET ${name} PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
      target_link_options(${name} INTERFACE ${XFT_LTO_LINK_OPTIONS})
    else()
      message(WARNING "xft: LTO unavailable: ${XFT_IPO_MSG}")
    endif()
  endif()
endfunction()

set(XFT_MAIN_ARGS "")
if(XFT_LIBC)
  list(APPEND XFT_MAIN_ARGS LIBC)
endif()
if(XFT_SANITIZE)
  list(APPEND XFT_MAIN_ARGS SANITIZE)
endif()
if(XFT_LTO)
  list(APPEND XFT_MAIN_ARGS LTO)
endif()

xft_add_lib(xft ${XFT_MAIN_ARGS})
add_library(xft::xft ALIAS xft)

set(SRCS_TEST
  tests/alloc/arena/arena_extend_test.c
  tests/alloc/arena/arena_extend_test_clean_releases.c
  tests/alloc/arena/arena_extend_test_rewind_grow.c
  tests/alloc/arena/arena_extend_test_rewind_reuse.c
  tests/alloc/arena/arena_extend_test_trigger.c
  tests/alloc/arena/arena_test.c
  tests/alloc/arena/arena_test_alignment.c
  tests/alloc/arena/arena_test_basic.c
  tests/alloc/arena/arena_test_checkpoint.c
  tests/alloc/arena/arena_test_invalid.c
  tests/alloc/arena/arena_test_uniq.c
  tests/alloc/gpa/gpa_bulk_test.c
  tests/alloc/gpa/gpa_bulk_test_mixed_sizes.c
  tests/alloc/gpa/gpa_bulk_test_mixed_sizes_fill.c
  tests/alloc/gpa/gpa_bulk_test_reuse.c
  tests/alloc/gpa/gpa_bulk_test_same_size.c
  tests/alloc/gpa/gpa_bulk_test_same_size_fill.c
  tests/alloc/vtables/vtables_test.c
  tests/alloc/vtables/vtables_test_arena.c
  tests/alloc/vtables/vtables_test_arena_realloc.c
  tests/alloc/vtables/vtables_test_gpa.c
  tests/alloc/vtables/vtables_test_gpa_freelist.c
  tests/alloc/vtables/vtables_test_gpa_freelist_advance.c
  tests/alloc/vtables/vtables_test_gpa_realloc.c
  tests/alloc/vtables/vtables_test_palloc.c
  tests/alloc/vtables/vtables_test_palloc_realloc.c
  tests/bmi/bmi_test.c
  tests/bmi/bmi_test_bswap.c
  tests/bmi/bmi_test_clz.c
  tests/bmi/bmi_test_ctz.c
  tests/bmi/bmi_test_max.c
  tests/containers/str/str_test.c
  tests/containers/str/str_test_extend.c
  tests/containers/str/str_test_new.c
  tests/containers/str/str_test_push_back.c
  tests/containers/str/str_test_remove.c
  tests/containers/swissmap/map_test.c
  tests/containers/swissmap/map_test_delete.c
  tests/containers/swissmap/map_test_insert_lookup.c
  tests/containers/swissmap/map_test_many.c
  tests/containers/swissmap/map_test_overwrite.c
  tests/containers/vec/vec_test.c
  tests/containers/vec/vec_test_clear_reuse.c
  tests/containers/vec/vec_test_extend.c
  tests/containers/vec/vec_test_pop.c
  tests/containers/vec/vec_test_push_get.c
  tests/cstr/cstr_to_str/cstr_to_str_test.c
  tests/cstr/strlen/strlen_test.c
  tests/cstr/strlen/strlen_test_basic.c
  tests/cstr/strlen/strlen_test_long.c
  tests/cstr/strlen/strlen_test_misaligned.c
  tests/hash/murmur3/murmur_test.c
  tests/hash/murmur3/murmur_test_deterministic.c
  tests/hash/murmur3/murmur_test_diff_input.c
  tests/hash/murmur3/murmur_test_lengths.c
  tests/hash/murmur3/murmur_test_seed.c
  tests/hash/xxh3/xxh3_test.c
  tests/hash/xxh3/xxh3_test_basic.c
  tests/hash/xxh3/xxh3_test_edge.c
  tests/hash/xxh3/xxh3_test_lengths.c
  tests/hash/xxh3/xxh3_test_lengths_large.c
  tests/hash/xxh3/xxh3_test_seeds.c
  tests/mem/bzero/bzero_test.c
  tests/mem/memchr/memchr_test.c
  tests/mem/memchr/memchr_test_basic.c
  tests/mem/memchr/memchr_test_edge.c
  tests/mem/memchr/memchr_test_long.c
  tests/mem/memchr/memchr_test_misaligned.c
  tests/mem/memcmp/memcmp_test.c
  tests/mem/memcmp/memcmp_test_basic.c
  tests/mem/memcmp/memcmp_test_binary.c
  tests/mem/memcmp/memcmp_test_long.c
  tests/mem/memcmp/memcmp_test_misaligned.c
  tests/mem/memcpy/memcpy_test.c
  tests/mem/memcpy/memcpy_test_basic.c
  tests/mem/memcpy/memcpy_test_large.c
  tests/mem/memcpy/memcpy_test_misaligned.c
  tests/mem/memmove/memmove_test.c
  tests/mem/memset/memset_test.c
  tests/mem/memset/memset_test_basic.c
  tests/mem/memset/memset_test_large.c
  tests/mem/memset/memset_test_misaligned.c
  tests/mem/streaming/streaming_test.c
  tests/mem/streaming/streaming_test_memcpy.c
  tests/mem/streaming/streaming_test_memset.c
  tests/rng/xoshiro/xoshiro_test.c
  tests/rng/xoshiro/xoshiro_test_basic.c
  tests/rng/xoshiro/xoshiro_test_init_diff.c
  tests/rng/xoshiro/xoshiro_test_not_constant.c
  tests/rng/xoshiro/xoshiro_test_state_changes.c
  tests/test_state.c
  tests/tests_main.c)

set(FUZZ_TARGETS
  fuzz_mem fuzz/mem_fuzz.c
  fuzz_vec fuzz/vec_fuzz.c
  fuzz_map fuzz/map_fuzz.c)

set(SRCS_BENCH_memcpy_bench
  bench/memcpy/memcpy_bench.c
  bench/memcpy/memcpy_bench_large.c
  bench/memcpy/memcpy_bench_medium.c
  bench/memcpy/memcpy_bench_short.c
  bench/memcpy/memcpy_bench_varied.c)

set(SRCS_BENCH_memcpy_stream_bench
  bench/memcpy/memcpy_stream_bench.c
  bench/memcpy/memcpy_bench_stream.c)

set(SRCS_BENCH_memmove_bench
  bench/memmove/memmove_bench.c
  bench/memmove/memmove_bench_large.c
  bench/memmove/memmove_bench_medium.c
  bench/memmove/memmove_bench_short.c
  bench/memmove/memmove_bench_utils.c
  bench/memmove/memmove_bench_varied.c)

set(SRCS_BENCH_memset_bench
  bench/memset/memset_bench.c
  bench/memset/memset_bench_large.c
  bench/memset/memset_bench_medium.c
  bench/memset/memset_bench_short.c
  bench/memset/memset_bench_varied.c)

set(SRCS_BENCH_memset_stream_bench
  bench/memset/memset_stream_bench.c
  bench/memset/memset_bench_stream.c)

set(SRCS_BENCH_gpa_bench
  bench/gpa/gpa_bench.c
  bench/gpa/gpa_bench_bulk.c
  bench/gpa/gpa_bench_get.c
  bench/gpa/gpa_bench_ops.c
  bench/gpa/gpa_bench_rand.c)

set(SRCS_BENCH_arena_bench
  bench/arena/arena_bench.c
  bench/arena/arena_bench_ops.c
  bench/arena/arena_bench_rand.c)

set(SRCS_BENCH_vec_bench
  bench/vec/vec_bench.c
  bench/vec/vec_bench_extend.c
  bench/vec/vec_bench_ops.c
  bench/vec/vec_bench_read.c
  bench/vec/vec_bench_remove.c
  bench/vec/vec_bench_state.c)

set(BENCH_TARGETS
  memcpy_bench memcpy_stream_bench memmove_bench memset_bench
  memset_stream_bench gpa_bench arena_bench vec_bench)

function(xft_add_harness name)
  cmake_parse_arguments(H "" "LIB" "SOURCES;INCLUDES" ${ARGN})
  add_executable(${name} ${H_SOURCES})
  target_link_libraries(${name} PRIVATE ${H_LIB})
  target_include_directories(${name} PRIVATE ${H_INCLUDES})
  target_compile_definitions(${name} PRIVATE ${XFT_DEFINES_PRIVATE})
  target_compile_options(${name} PRIVATE
    ${CFLAGS} ${WARNS} $<$<CONFIG:Release,RelWithDebInfo,>:-O3>)
endfunction()

if(XFT_BUILD_TESTS OR XFT_BUILD_FUZZ)
  if(XFT_SANITIZE)
    set(XFT_HARNESS_LIB xft)  # main lib is already the sanitized hosted build
  else()
    xft_add_lib(xft-san SANITIZE)
    set(XFT_HARNESS_LIB xft-san)
  endif()
  enable_testing()
endif()

if(XFT_BUILD_TESTS)
  xft_add_harness(tests LIB ${XFT_HARNESS_LIB} SOURCES ${SRCS_TEST})
  add_test(NAME tests COMMAND tests)
  set_tests_properties(tests PROPERTIES LABELS unit)
endif()

if(XFT_BUILD_FUZZ)
  add_custom_target(fuzz COMMENT "fuzz targets")
  while(FUZZ_TARGETS)
    list(POP_FRONT FUZZ_TARGETS _name _src)
    xft_add_harness(${_name} LIB ${XFT_HARNESS_LIB} SOURCES ${_src} INCLUDES fuzz)
    add_dependencies(fuzz ${_name})
    add_test(NAME ${_name} COMMAND ${_name})
    set_tests_properties(${_name} PROPERTIES LABELS fuzz)
  endwhile()
endif()

if(XFT_BUILD_BENCH)
  add_custom_target(bench COMMENT "benchmarks")
  set(XFT_BENCH_RUN "")
  foreach(b IN LISTS BENCH_TARGETS)
    xft_add_harness(${b} LIB xft SOURCES ${SRCS_BENCH_${b}} INCLUDES bench/include)
    add_dependencies(bench ${b})
    list(APPEND XFT_BENCH_RUN COMMAND $<TARGET_FILE:${b}>)
  endforeach()
  add_custom_target(run-bench ${XFT_BENCH_RUN}
    DEPENDS ${BENCH_TARGETS}
    COMMENT "running benchmarks"
    USES_TERMINAL VERBATIM)
endif()

find_program(XFT_SCAN_BUILD scan-build)
find_program(XFT_NORMINETTE norminette)

set(XFT_ANALYZE_DEFS "")
foreach(d IN LISTS XFT_DEFINES_PUBLIC XFT_DEFINES_PRIVATE)
  list(APPEND XFT_ANALYZE_DEFS "-D${d}")
endforeach()

add_custom_target(analyze
  COMMAND ${CMAKE_C_COMPILER} ${CFLAGS} ${WARNS} -fanalyzer
          -I${CMAKE_CURRENT_SOURCE_DIR}/include
          ${XFT_ANALYZE_DEFS}
          -fsyntax-only ${SRCS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "static analysis (${XFT_FLAVOR})"
  VERBATIM)

include(GNUInstallDirs)
install(TARGETS xft ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
