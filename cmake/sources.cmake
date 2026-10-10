# every source list. needs options.cmake (XFT_WIN64, XFT_RT, XFT_STRICT_ARCH)

set(SRCS_ALLOC
  src/alloc/arena/xft_arena.c
  src/alloc/arena/xft_arena_alloc.c
  src/alloc/arena/xft_arena_alloc_scopes.c
  src/alloc/arena/xft_arena_alloc_utils.c
  src/alloc/arena/xft_arena_rewind.c
  src/alloc/arena/xft_arena_vtable.c
  src/alloc/xft_alloc_clone.c
  src/alloc/gpa/xft_gpa.c
  src/alloc/gpa/xft_gpa_alloc.c
  src/alloc/gpa/xft_gpa_free.c
  src/alloc/gpa/xft_gpa_realloc.c
  src/alloc/gpa/xft_gpa_vtable.c
  src/alloc/huge_matcher/xft_huge_matcher.c
  src/alloc/page_allocator/xft_palloc.c
  src/alloc/page_allocator/xft_palloc_vtable.c
  src/alloc/report/xft_report.c
  src/alloc/report/xft_report_alloc.c
  src/alloc/report/xft_report_free.c
  src/alloc/report/xft_report_realloc.c
  src/alloc/report/xft_report_vtable.c)

set(SRCS_ATOMICS
  src/atomics/mutex/xft_mutex_backoff_portable.c
  src/atomics/mutex/xft_mutex_busy.c
  src/atomics/mutex/xft_mutex_fast.c
  src/atomics/mutex/xft_mutex_init.c
  src/atomics/mutex/xft_mutex_lock.c
  src/atomics/mutex/xft_mutex_slow.c
  src/atomics/mutex/xft_mutex_unlock.c)

set(SRCS_BMI
  src/bmi/__hasz.c
  src/bmi/__max.c
  src/bmi/__maxs.c
  src/bmi/__populate.c
  src/bmi/xft_align.c
  src/bmi/xft_bswap.c
  src/bmi/xft_memclz.c
  src/bmi/xft_memctz.c
  src/bmi/xft_next_pow2.c
  src/bmi/xft_popcount.c
  src/bmi/xft_rollmask.c
  src/bmi/xft_rotl.c
  src/bmi/xft_tern.c
  src/bmi/xft_to_be_from_be.c
  src/bmi/xft_to_be_from_le.c
  src/bmi/vmanip/vec128/xft_eqmask.c
  src/bmi/vmanip/vec128/xft_mask.c
  src/bmi/vmanip/vec128/xft_rangemask.c
  src/bmi/vmanip/vec128/xft_splat.c
  src/bmi/vmanip/vec128/xft_testmask.c
  src/bmi/vmanip/vec256/xft_eqmask.c
  src/bmi/vmanip/vec256/xft_mask.c
  src/bmi/vmanip/vec256/xft_rangemask.c
  src/bmi/vmanip/vec256/xft_splat.c
  src/bmi/vmanip/vec256/xft_testmask.c
  src/bmi/vmanip/vec512/xft_eqmask.c
  src/bmi/vmanip/vec512/xft_mask.c
  src/bmi/vmanip/vec512/xft_rangemask.c
  src/bmi/vmanip/vec512/xft_splat.c
  src/bmi/vmanip/vec512/xft_testmask.c)

set(SRCS_CONTAINERS
  src/containers/str/xft_str.c
  src/containers/str/xft_str_extend.c
  src/containers/str/xft_str_push_back.c
  src/containers/str/xft_str_remove.c
  src/containers/swissmap/xft_map.c
  src/containers/swissmap/xft_map_delete.c
  src/containers/swissmap/xft_map_insert.c
  src/containers/swissmap/xft_map_insert_unchecked.c
  src/containers/swissmap/xft_map_lookup.c
  src/containers/swissmap/xft_map_rehash.c
  src/containers/vec/xft_vec.c
  src/containers/vec/xft_vec_bytesize.c
  src/containers/vec/xft_vec_extend.c
  src/containers/vec/xft_vec_free.c
  src/containers/vec/xft_vec_get.c
  src/containers/vec/xft_vec_pop.c
  src/containers/vec/xft_vec_push_back.c
  src/containers/vec/xft_vec_remove.c)

set(SRCS_CSTR
  src/cstr/xft_cstr_to_str.c
  src/cstr/xft_strlen.c)

set(SRCS_CTYPE
  src/ctype/xft_isalnum.c
  src/ctype/xft_isalpha.c
  src/ctype/xft_isascii.c
  src/ctype/xft_isdigit.c
  src/ctype/xft_isprint.c
  src/ctype/xft_isspace.c
  src/ctype/xft_isxdigit.c)

set(SRCS_FMT
  src/fmt/fmt.c
  src/fmt/xft_fmt_handle_double.c
  src/fmt/xft_fmt_handle_hex.c
  src/fmt/xft_fmt_handle_signed.c
  src/fmt/xft_fmt_handle_slice.c
  src/fmt/xft_fmt_handle_unsigned.c)

set(SRCS_FUZZER
  src/fuzzer/xft_fuzzer.c
  src/fuzzer/xft_fuzzer_get_rand.c
  src/fuzzer/xft_fuzzer_initrand.c)

set(SRCS_HASH
  src/hash/murmur3/xft_murmur3.c
  src/hash/murmur3/xft_murmur3_tail.c
  src/hash/murmur3/xft_murmur_helpers.c
  src/hash/xxh3/xft_xxh3.c
  src/hash/xxh3/xft_xxh3_avalanche.c
  src/hash/xxh3/xft_xxh3_finalizers.c
  src/hash/xxh3/xft_xxh3_large_sizes.c
  src/hash/xxh3/xft_xxh3_medium_sizes.c
  src/hash/xxh3/xft_xxh3_mul128_fold64.c
  src/hash/xxh3/xft_xxh3_rrmxmx.c
  src/hash/xxh3/xft_xxh3_secret.c
  src/hash/xxh3/xft_xxh3_small_sizes.c
  src/hash/xxh3/xft_xxh3_xorshift.c)

set(SRCS_HINT
  src/hint/xft_assume.c
  src/hint/xft_hardcrash.c
  src/hint/xft_pin_invariant.c)

set(SRCS_IO
  src/io/blocking_fd/xft_drain.c
  src/io/blocking_fd/xft_fill.c
  src/io/blocking_fd/xft_flush.c
  src/io/blocking_fd/xft_vtable.c
  src/io/xft_get_fixed_fd.c
  src/io/xft_get_fixed_fd_win64.c
  src/io/xft_map_file.c
  src/io/xft_reader_read.c
  src/io/xft_writer_write.c
  src/io/raw_buffer/xft_drain.c
  src/io/raw_buffer/xft_fill.c
  src/io/raw_buffer/xft_flush.c
  src/io/raw_buffer/xft_vtable.c)

set(SRCS_MATH
  src/math/3d/xft_3dadd.c
  src/math/3d/xft_3dcross.c
  src/math/3d/xft_3ddiv.c
  src/math/3d/xft_3ddot.c
  src/math/3d/xft_3dmul.c
  src/math/3d/xft_3dnorm.c
  src/math/3d/xft_3dsub.c
  src/math/3d/xft_3dunit.c
  src/math/sqrt/xft_rsqrt.c
  src/math/sqrt/xft_sqrt.c
  src/math/xft_fabs.c
  src/math/xft_pow.c
  src/math/xft_pow_signed.c
  src/math/xft_round.c
)

set(SRCS_MEM
  src/mem/arch/xft_memchr.c
  src/mem/arch/xft_memcmp.c
  src/mem/arch/xft_memcpy.c
  src/mem/arch/xft_memmove.c
  src/mem/arch/xft_memset.c
  src/mem/xft_align.c
  src/mem/xft_bzero.c
  src/mem/xft_fatptr.c
  src/mem/xft_fences.c
  src/mem/xft_ldfence.c
  src/mem/xft_membroadcast.c
  src/mem/xft_memtake.c
  src/mem/xft_movs.c
  src/mem/xft_overlap.c
  src/mem/xft_prefetch_intrin.c
  src/mem/xft_prefetch_noop.c
  src/mem/xft_stfence.c
  src/mem/hugebranches/xft_memcpy_huge.c
  src/mem/hugebranches/xft_memmove_huge.c
  src/mem/hugebranches/xft_memset_huge.c
  src/mem/portable/xft_memcpy.c
  src/mem/portable/xft_memset.c
  src/mem/streaming/xft_memcpy_streaming.c
  src/mem/streaming/xft_memset_streaming.c
  src/mem/vec128/xft_memchr.c
  src/mem/vec128/xft_memcmp.c
  src/mem/vec128/xft_memcpy.c
  src/mem/vec128/xft_memset.c
  src/mem/vec256/xft_memchr_vec256.c
  src/mem/vec256/xft_memcmp_vec256.c
  src/mem/vec256/xft_memcpy_vec256.c
  src/mem/vec256/xft_memset_vec256.c
  src/mem/vec512/xft_memchr_vec512.c
  src/mem/vec512/xft_memcmp_vec512.c
  src/mem/vec512/xft_memcpy_vec512.c
  src/mem/vec512/xft_memset_vec512.c)

set(SRCS_RNG src/rng/xft_xoshiro256ss.c)

set(SRCS_RT_linux
  src/rt/linux/xft_free_kernel_ptrs.c
  src/rt/linux/xft_get_kernel_ptrs.c
  src/rt/linux/xft_get_rt.c)

set(SRCS_RT_win64
  src/rt/win64/xft_free_kernel_ptrs.c
  src/rt/win64/xft_get_kernel_ptrs.c
  src/rt/win64/xft_get_rt.c)

if(XFT_WIN64)
  set(SRCS_RT ${SRCS_RT_win64})
else()
  set(SRCS_RT ${SRCS_RT_linux})
endif()

set(SRCS_SIGNALS src/signals/xft_sigfillset.c)

set(SRCS_SORT
  src/sort/xft_qsort.c
  src/sort/xft_qsort_u64s.c)

set(SRCS_SYSCALLS
  src/syscalls/linux/xft_mmap_commit.c
  src/syscalls/xft_get_cpu_count.c
  src/syscalls/xft_map_failed.c)

set(SRCS_TIME
  src/time/xft_get_nanos.c
  src/time/xft_rdtsc.c)

set(MODULES ALLOC ATOMICS BMI CONTAINERS CSTR CTYPE FMT FUZZER HASH HINT IO
            MATH MEM RNG RT SIGNALS SORT SYSCALLS TIME)

set(SRCS_ARCH_x86_64
  src/atomics/mutex/xft_mutex_backoff_x86_64.c
  src/bmi/x86_64/xft_bswap.c
  src/bmi/x86_64/xft_memclz.c
  src/bmi/x86_64/xft_memctz.c
  src/bmi/x86_64/xft_popcount.c)

set(SRCS_ARCH_aarch64
  src/atomics/mutex/xft_mutex_backoff_aarch64.c
  src/bmi/aarch64/xft_bswap.c
  src/bmi/aarch64/xft_memclz.c
  src/bmi/aarch64/xft_memctz.c
  src/bmi/aarch64/xft_popcount_neon.c)

set(SRCS_RT_ENTRY_x86_64  src/rt/linux/x86_64/xft_rt.c)
set(SRCS_RT_ENTRY_aarch64 src/rt/linux/aarch64/xft_rt.c)
set(SRCS_RT_ENTRY_libc    src/rt/libc/xft_rt.c)
set(SRCS_RT_ENTRY_win64   src/rt/win64/xft_rt.c)

# the syscall backends implement the same set; only the deltas are listed
set(_xft_syscalls
  clock_gettime
  clone
  close
  exit
  fmap
  fork
  futex
  getpid
  ioctl
  lockf
  mkdir
  mmap
  mprotect
  mremap
  open
  perf_events
  read
  sched_getaffinity
  sched_setaffinity
  set_tid_address
  sigprocmask
  stat
  wait4
  write
  writev)

# _xft_syscall_srcs(<out> <dir> [ADD <name>...] [REMOVE <name>...])
function(_xft_syscall_srcs out dir)
  cmake_parse_arguments(A "" "" "ADD;REMOVE" ${ARGN})
  set(_names ${_xft_syscalls} ${A_ADD})
  if(A_REMOVE)
    list(REMOVE_ITEM _names ${A_REMOVE})
  endif()
  list(SORT _names)
  list(TRANSFORM _names PREPEND src/syscalls/${dir}/xft_)
  list(TRANSFORM _names APPEND .c)
  set(${out} ${_names} PARENT_SCOPE)
endfunction()

_xft_syscall_srcs(SRCS_FREESTANDING_x86_64 linux/x86_64)
_xft_syscall_srcs(SRCS_FREESTANDING_aarch64 linux/aarch64 ADD syscall6)
_xft_syscall_srcs(SRCS_LIBC linux/libc)
_xft_syscall_srcs(SRCS_WIN64 win64 REMOVE ioctl perf_events)

if(XFT_STRICT_ARCH)
  set(XFT_BACKEND_ARCHS ${XFT_ARCH})
else()
  set(XFT_BACKEND_ARCHS x86_64 aarch64)
endif()

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

set(SRCS_BENCH_memcpy_bench
  bench/memcpy/memcpy_bench.c
  bench/memcpy/memcpy_bench_large.c
  bench/memcpy/memcpy_bench_medium.c
  bench/memcpy/memcpy_bench_short.c
  bench/memcpy/memcpy_bench_varied.c)

set(SRCS_BENCH_memcpy_stream_bench
  bench/memcpy/memcpy_stream_bench.c
  bench/memcpy/memcpy_bench_stream.c)

set(SRCS_BENCH_strlen_bench
  bench/strlen/strlen_bench.c
  bench/strlen/strlen_bench_large.c
  bench/strlen/strlen_bench_medium.c
  bench/strlen/strlen_bench_short.c
  bench/strlen/strlen_bench_utils.c
  bench/strlen/strlen_bench_varied.c)

set(SRCS_BENCH_libc_bench
  bench/libc/libc_bench.c
  bench/libc/libc_bench_run.c
  bench/libc/libc_memcpy_large.c
  bench/libc/libc_memcpy_medium.c
  bench/libc/libc_memcpy_short.c
  bench/libc/libc_memcpy_varied.c
  bench/libc/libc_strlen_large.c
  bench/libc/libc_strlen_medium.c
  bench/libc/libc_strlen_short.c
  bench/libc/libc_strlen_varied.c
  bench/strlen/strlen_bench_utils.c)

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
