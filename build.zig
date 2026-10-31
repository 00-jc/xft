const std = @import("std");

const SRCS = [_][]const u8{
    "src/alloc/arena/xft_arena.c",
    "src/alloc/arena/xft_arena_alloc.c",
    "src/alloc/arena/xft_arena_alloc_scopes.c",
    "src/alloc/arena/xft_arena_alloc_utils.c",
    "src/alloc/arena/xft_arena_rewind.c",
    "src/alloc/arena/xft_arena_vtable.c",
    "src/alloc/xft_alloc_clone.c",
    "src/alloc/gpa/xft_gpa.c",
    "src/alloc/gpa/xft_gpa_alloc.c",
    "src/alloc/gpa/xft_gpa_free.c",
    "src/alloc/gpa/xft_gpa_realloc.c",
    "src/alloc/gpa/xft_gpa_vtable.c",
    "src/alloc/huge_matcher/xft_huge_matcher.c",
    "src/alloc/page_allocator/xft_palloc.c",
    "src/alloc/page_allocator/linux/xft_palloc.c",
    "src/alloc/page_allocator/win32/xft_palloc.c",
    "src/alloc/page_allocator/xft_palloc_vtable.c",
    "src/alloc/report/xft_report.c",
    "src/alloc/report/xft_report_alloc.c",
    "src/alloc/report/xft_report_free.c",
    "src/alloc/report/xft_report_realloc.c",
    "src/alloc/report/xft_report_vtable.c",
    "src/alloc/thread_safe/xft_ts_arena.c",
    "src/alloc/thread_safe/xft_ts_gpa.c",
    "src/alloc/thread_safe/xft_ts_reporta.c",
    "src/alloc/thread_safe/xft_ts_vtable.c",
    "src/atomics/mutex/xft_mutex_backoff_portable.c",
    "src/atomics/mutex/xft_mutex_busy.c",
    "src/atomics/mutex/xft_mutex_init.c",
    "src/atomics/mutex/xft_mutex_lock.c",
    "src/arch/xft_cache_line_size.c",
    "src/atomics/mutex/xft_mutex_fast.c",
    "src/atomics/mutex/xft_mutex_slow.c",
    "src/atomics/mutex/xft_mutex_unlock.c",
    "src/atomics/xft_signal.c",
    "src/bmi/xft_align.c",
    "src/bmi/xft_bswap.c",
    "src/bmi/xft_bswap_builtin.c",
    "src/bmi/xft_from_be.c",
    "src/bmi/xft_from_le.c",
    "src/bmi/xft_hasz.c",
    "src/bmi/xft_max.c",
    "src/bmi/xft_maxs.c",
    "src/bmi/xft_memclz.c",
    "src/bmi/xft_memclz_builtin.c",
    "src/bmi/xft_memctz.c",
    "src/bmi/xft_memctz_builtin.c",
    "src/bmi/xft_next_pow2.c",
    "src/bmi/xft_popcount.c",
    "src/bmi/xft_popcount_builtin.c",
    "src/bmi/xft_populate.c",
    "src/bmi/xft_rollmask.c",
    "src/bmi/xft_rotl.c",
    "src/bmi/xft_tern.c",
    "src/bmi/xft_to_be_from_be.c",
    "src/bmi/xft_to_be_from_le.c",
    "src/bmi/xft_to_le_from_be.c",
    "src/bmi/xft_to_le_from_le.c",
    "src/bmi/native/xft_iota.c",
    "src/bmi/native/xft_eqmask.c",
    "src/bmi/native/xft_mask.c",
    "src/bmi/native/xft_masked_load.c",
    "src/bmi/native/xft_rangemask.c",
    "src/bmi/native/xft_splat.c",
    "src/bmi/native/xft_testmask.c",
    "src/bmi/native/xft_compress_mask.c",
    "src/bmi/vmanip/vec128/xft_iota.c",
    "src/bmi/vmanip/vec128/xft_compress_mask.c",
    "src/bmi/vmanip/vec128/xft_eqmask.c",
    "src/bmi/vmanip/vec128/xft_mask.c",
    "src/bmi/vmanip/vec128/xft_masked_load.c",
    "src/bmi/vmanip/vec128/xft_rangemask.c",
    "src/bmi/vmanip/vec128/xft_splat.c",
    "src/bmi/vmanip/vec128/xft_testmask.c",
    "src/bmi/vmanip/vec256/xft_iota.c",
    "src/bmi/vmanip/vec256/xft_compress_mask.c",
    "src/bmi/vmanip/vec256/xft_eqmask.c",
    "src/bmi/vmanip/vec256/xft_mask.c",
    "src/bmi/vmanip/vec256/xft_masked_load.c",
    "src/bmi/vmanip/vec256/xft_rangemask.c",
    "src/bmi/vmanip/vec256/xft_splat.c",
    "src/bmi/vmanip/vec256/xft_testmask.c",
    "src/bmi/vmanip/vec512/xft_iota.c",
    "src/bmi/vmanip/vec512/xft_compress_mask.c",
    "src/bmi/vmanip/vec512/xft_eqmask.c",
    "src/bmi/vmanip/vec512/xft_mask.c",
    "src/bmi/vmanip/vec512/xft_masked_load.c",
    "src/bmi/vmanip/vec512/xft_rangemask.c",
    "src/bmi/vmanip/vec512/xft_splat.c",
    "src/bmi/vmanip/vec512/xft_testmask.c",
    "src/bmi/vmanip/vec128_16/xft_compress_mask.c",
    "src/bmi/vmanip/vec128_16/xft_eqmask.c",
    "src/bmi/vmanip/vec128_16/xft_iota.c",
    "src/bmi/vmanip/vec128_16/xft_mask.c",
    "src/bmi/vmanip/vec128_16/xft_masked_load.c",
    "src/bmi/vmanip/vec128_16/xft_rangemask.c",
    "src/bmi/vmanip/vec128_16/xft_splat.c",
    "src/bmi/vmanip/vec128_16/xft_testmask.c",
    "src/bmi/vmanip/vec256_16/xft_compress_mask.c",
    "src/bmi/vmanip/vec256_16/xft_eqmask.c",
    "src/bmi/vmanip/vec256_16/xft_iota.c",
    "src/bmi/vmanip/vec256_16/xft_mask.c",
    "src/bmi/vmanip/vec256_16/xft_masked_load.c",
    "src/bmi/vmanip/vec256_16/xft_rangemask.c",
    "src/bmi/vmanip/vec256_16/xft_splat.c",
    "src/bmi/vmanip/vec256_16/xft_testmask.c",
    "src/bmi/vmanip/vec512_16/xft_compress_mask.c",
    "src/bmi/vmanip/vec512_16/xft_eqmask.c",
    "src/bmi/vmanip/vec512_16/xft_iota.c",
    "src/bmi/vmanip/vec512_16/xft_mask.c",
    "src/bmi/vmanip/vec512_16/xft_masked_load.c",
    "src/bmi/vmanip/vec512_16/xft_rangemask.c",
    "src/bmi/vmanip/vec512_16/xft_splat.c",
    "src/bmi/vmanip/vec512_16/xft_testmask.c",
    "src/bmi/native_16/xft_compress_mask.c",
    "src/bmi/native_16/xft_eqmask.c",
    "src/bmi/native_16/xft_iota.c",
    "src/bmi/native_16/xft_mask.c",
    "src/bmi/native_16/xft_masked_load.c",
    "src/bmi/native_16/xft_rangemask.c",
    "src/bmi/native_16/xft_splat.c",
    "src/bmi/native_16/xft_testmask.c",
    "src/bmi/vmanip/vec128_32/xft_compress_mask.c",
    "src/bmi/vmanip/vec128_32/xft_eqmask.c",
    "src/bmi/vmanip/vec128_32/xft_iota.c",
    "src/bmi/vmanip/vec128_32/xft_mask.c",
    "src/bmi/vmanip/vec128_32/xft_masked_load.c",
    "src/bmi/vmanip/vec128_32/xft_rangemask.c",
    "src/bmi/vmanip/vec128_32/xft_splat.c",
    "src/bmi/vmanip/vec128_32/xft_testmask.c",
    "src/bmi/vmanip/vec256_32/xft_compress_mask.c",
    "src/bmi/vmanip/vec256_32/xft_eqmask.c",
    "src/bmi/vmanip/vec256_32/xft_iota.c",
    "src/bmi/vmanip/vec256_32/xft_mask.c",
    "src/bmi/vmanip/vec256_32/xft_masked_load.c",
    "src/bmi/vmanip/vec256_32/xft_rangemask.c",
    "src/bmi/vmanip/vec256_32/xft_splat.c",
    "src/bmi/vmanip/vec256_32/xft_testmask.c",
    "src/bmi/vmanip/vec512_32/xft_compress_mask.c",
    "src/bmi/vmanip/vec512_32/xft_eqmask.c",
    "src/bmi/vmanip/vec512_32/xft_iota.c",
    "src/bmi/vmanip/vec512_32/xft_mask.c",
    "src/bmi/vmanip/vec512_32/xft_masked_load.c",
    "src/bmi/vmanip/vec512_32/xft_rangemask.c",
    "src/bmi/vmanip/vec512_32/xft_splat.c",
    "src/bmi/vmanip/vec512_32/xft_testmask.c",
    "src/bmi/native_32/xft_compress_mask.c",
    "src/bmi/native_32/xft_eqmask.c",
    "src/bmi/native_32/xft_iota.c",
    "src/bmi/native_32/xft_mask.c",
    "src/bmi/native_32/xft_masked_load.c",
    "src/bmi/native_32/xft_rangemask.c",
    "src/bmi/native_32/xft_splat.c",
    "src/bmi/native_32/xft_testmask.c",
    "src/bmi/vmanip/vec128_64/xft_compress_mask.c",
    "src/bmi/vmanip/vec128_64/xft_eqmask.c",
    "src/bmi/vmanip/vec128_64/xft_iota.c",
    "src/bmi/vmanip/vec128_64/xft_mask.c",
    "src/bmi/vmanip/vec128_64/xft_masked_load.c",
    "src/bmi/vmanip/vec128_64/xft_rangemask.c",
    "src/bmi/vmanip/vec128_64/xft_splat.c",
    "src/bmi/vmanip/vec128_64/xft_testmask.c",
    "src/bmi/vmanip/vec256_64/xft_compress_mask.c",
    "src/bmi/vmanip/vec256_64/xft_eqmask.c",
    "src/bmi/vmanip/vec256_64/xft_iota.c",
    "src/bmi/vmanip/vec256_64/xft_mask.c",
    "src/bmi/vmanip/vec256_64/xft_masked_load.c",
    "src/bmi/vmanip/vec256_64/xft_rangemask.c",
    "src/bmi/vmanip/vec256_64/xft_splat.c",
    "src/bmi/vmanip/vec256_64/xft_testmask.c",
    "src/bmi/vmanip/vec512_64/xft_compress_mask.c",
    "src/bmi/vmanip/vec512_64/xft_eqmask.c",
    "src/bmi/vmanip/vec512_64/xft_iota.c",
    "src/bmi/vmanip/vec512_64/xft_mask.c",
    "src/bmi/vmanip/vec512_64/xft_masked_load.c",
    "src/bmi/vmanip/vec512_64/xft_rangemask.c",
    "src/bmi/vmanip/vec512_64/xft_splat.c",
    "src/bmi/vmanip/vec512_64/xft_testmask.c",
    "src/bmi/native_64/xft_compress_mask.c",
    "src/bmi/native_64/xft_eqmask.c",
    "src/bmi/native_64/xft_iota.c",
    "src/bmi/native_64/xft_mask.c",
    "src/bmi/native_64/xft_masked_load.c",
    "src/bmi/native_64/xft_rangemask.c",
    "src/bmi/native_64/xft_splat.c",
    "src/bmi/native_64/xft_testmask.c",
    "src/containers/indexmap/xft_indexmap_get_arrays.c",
    "src/containers/indexmap/xft_indexmap.c",
    "src/containers/indexmap/xft_indexmap_ctx.c",
    "src/containers/indexmap/xft_indexmap_delete.c",
    "src/containers/indexmap/xft_indexmap_insert.c",
    "src/containers/indexmap/xft_indexmap_lookup.c",
    "src/containers/indexmap/xft_indexmap_probe.c",
    "src/containers/indexmap/xft_indexmap_probe_seeded.c",
    "src/containers/indexmap/xft_indexmap_slot.c",
    "src/containers/indexmap/xft_indexmap_iterate.c",
    "src/containers/soa/xft_soa.c",
    "src/containers/soa/xft_soa_append.c",
    "src/containers/soa/xft_soa_field.c",
    "src/containers/soa/xft_soa_reserve.c",
    "src/containers/str/xft_str.c",
    "src/containers/str/xft_str_extend.c",
    "src/containers/str/xft_str_push_back.c",
    "src/containers/str/xft_str_remove.c",
    "src/containers/swissmap/xft_swissmap.c",
    "src/containers/swissmap/xft_swissmap_ctx.c",
    "src/containers/swissmap/xft_swissmap_delete.c",
    "src/containers/swissmap/xft_swissmap_insert.c",
    "src/containers/swissmap/xft_swissmap_lookup.c",
    "src/containers/swissmap/xft_swissmap_probe.c",
    "src/containers/swissmap/xft_swissmap_slot.c",
    "src/containers/vec/xft_vec.c",
    "src/containers/vec/xft_vec_bytesize.c",
    "src/containers/vec/xft_vec_extend.c",
    "src/containers/vec/xft_vec_free.c",
    "src/containers/vec/xft_vec_get.c",
    "src/containers/vec/xft_vec_pop.c",
    "src/containers/vec/xft_vec_push_back.c",
    "src/containers/vec/xft_vec_remove.c",
    "src/cstr/xft_cstr_to_str.c",
    "src/cstr/xft_strlen.c",
    "src/ctype/xft_isalnum.c",
    "src/ctype/xft_isalpha.c",
    "src/ctype/xft_isascii.c",
    "src/ctype/xft_isdigit.c",
    "src/ctype/xft_isprint.c",
    "src/ctype/xft_isspace.c",
    "src/ctype/xft_isxdigit.c",
    "src/fmt/fmt.c",
    "src/fmt/xft_fmt_handle_double.c",
    "src/fmt/xft_fmt_handle_hex.c",
    "src/fmt/xft_fmt_handle_signed.c",
    "src/fmt/xft_fmt_handle_slice.c",
    "src/fmt/xft_fmt_handle_unsigned.c",
    "src/fuzzer/xft_fuzzer.c",
    "src/fuzzer/xft_fuzzer_get_rand.c",
    "src/fuzzer/xft_fuzzer_initrand.c",
    "src/hash/murmur3/xft_murmur3.c",
    "src/hash/murmur3/xft_murmur3_tail.c",
    "src/hash/murmur3/xft_murmur_helpers.c",
    "src/hash/xxh3/xft_xxh3.c",
    "src/hash/xxh3/xft_xxh3_avalanche.c",
    "src/hash/xxh3/xft_xxh3_finalizers.c",
    "src/hash/xxh3/xft_xxh3_large_sizes.c",
    "src/hash/xxh3/xft_xxh3_medium_sizes.c",
    "src/hash/xxh3/xft_xxh3_mul128_fold64.c",
    "src/hash/xxh3/xft_xxh3_rrmxmx.c",
    "src/hash/xxh3/xft_xxh3_secret.c",
    "src/hash/xxh3/xft_xxh3_small_sizes.c",
    "src/hash/xxh3/xft_xxh3_xorshift.c",
    "src/hint/xft_assume.c",
    "src/hint/xft_hardcrash.c",
    "src/hint/xft_pin_invariant.c",
    "src/io/blocking_fd/linux/xft_drain.c",
    "src/io/blocking_fd/linux/xft_fill.c",
    "src/io/blocking_fd/linux/xft_flush.c",
    "src/io/blocking_fd/win32/xft_drain.c",
    "src/io/blocking_fd/win32/xft_fill.c",
    "src/io/blocking_fd/win32/xft_flush.c",
    "src/io/blocking_fd/xft_vtable.c",
    "src/io/file/linux/xft_file_info.c",
    "src/io/file/linux/xft_open_file.c",
    "src/io/file/win32/xft_file_info.c",
    "src/io/file/win32/xft_open_file.c",
    "src/io/xft_get_fixed_fd.c",
    "src/io/win32/xft_get_fixed_fd.c",
    "src/io/xft_map_file.c",
    "src/io/xft_reader_read.c",
    "src/io/xft_writer_write.c",
    "src/io/raw_buffer/xft_drain.c",
    "src/io/raw_buffer/xft_fill.c",
    "src/io/raw_buffer/xft_flush.c",
    "src/io/raw_buffer/xft_vtable.c",
    "src/math/3d/xft_3dadd.c",
    "src/math/3d/xft_3dcross.c",
    "src/math/3d/xft_3ddiv.c",
    "src/math/3d/xft_3ddot.c",
    "src/math/3d/xft_3dmul.c",
    "src/math/3d/xft_3dnorm.c",
    "src/math/3d/xft_3dsub.c",
    "src/math/3d/xft_3dunit.c",
    "src/math/sqrt/xft_rsqrt.c",
    "src/math/sqrt/xft_sqrt.c",
    "src/math/xft_fabs.c",
    "src/math/xft_pow.c",
    "src/math/xft_pow_signed.c",
    "src/math/xft_round.c",
    "src/mem/arch/xft_memchr.c",
    "src/mem/arch/xft_memcmp.c",
    "src/mem/arch/xft_memcpy.c",
    "src/mem/arch/xft_memmove.c",
    "src/mem/arch/xft_memset.c",
    "src/mem/xft_align.c",
    "src/mem/xft_bzero.c",
    "src/mem/xft_fatptr.c",
    "src/mem/xft_fences.c",
    "src/mem/xft_ldfence.c",
    "src/mem/xft_membroadcast.c",
    "src/mem/xft_memtake.c",
    "src/mem/xft_movs.c",
    "src/mem/xft_overlap.c",
    "src/mem/xft_prefetch_read.c",
    "src/mem/xft_prefetch_write.c",
    "src/mem/xft_scalar_mask_load.c",
    "src/mem/xft_stfence.c",
    "src/mem/hugebranches/xft_memcpy_huge.c",
    "src/mem/hugebranches/xft_memmove_huge.c",
    "src/mem/hugebranches/xft_memset_huge.c",
    "src/mem/portable/xft_memcpy.c",
    "src/mem/portable/xft_memset.c",
    "src/mem/streaming/xft_memcpy_streaming.c",
    "src/mem/streaming/xft_memset_streaming.c",
    "src/mem/vec128/xft_memcpy.c",
    "src/mem/vec128/xft_memset.c",
    "src/mem/vec256/xft_memcpy_vec256.c",
    "src/mem/vec256/xft_memset_vec256.c",
    "src/mem/vec512/xft_memcpy_vec512.c",
    "src/mem/vec512/xft_memset_vec512.c",
    "src/rng/xft_xoshiro256ss.c",
    "src/rt/xft_dyn_cpu_select.c",
    "src/rt/xft_exit_process.c",
    "src/rt/xft_set_static_rt.c",
    "src/sort/xft_qsort.c",
    "src/sort/xft_qsort_u64s.c",
    "src/os/linux/xft_mmap_commit.c",
    "src/os/linux/xft_map_failed.c",
    "src/os/xft_get_cpu_count.c",
    "src/time/linux/xft_get_nanos.c",
    "src/time/win32/xft_get_nanos.c",
    "src/time/xft_rdtsc.c",
};

const SRCS_RT_linux = [_][]const u8{
    "src/rt/linux/xft_kernel_ptrs_destroy.c",
    "src/rt/linux/xft_get_kernel_ptrs.c",
    "src/rt/linux/xft_get_rt.c",
    "src/rt/linux/xft_get_sysinfo.c",
    "src/rt/linux/xft_start_tls_for_main_thread.c",
};

const SRCS_THREADS_linux = [_][]const u8{
    "src/threads/linux/xft_thread_spawn.c",
    "src/threads/linux/xft_thread_join.c",
    "src/threads/linux/xft_thread_detach.c",
};

const SRCS_FUTEX_x86_64 = [_][]const u8{
    "src/atomics/futex/linux/x86_64/xft_futex_wait.c",
    "src/atomics/futex/linux/x86_64/xft_futex_wake.c",
};

const SRCS_FUTEX_aarch64 = [_][]const u8{
    "src/atomics/futex/linux/aarch64/xft_futex_wait.c",
    "src/atomics/futex/linux/aarch64/xft_futex_wake.c",
};

const SRCS_FUTEX_libc = [_][]const u8{
    "src/atomics/futex/linux/libc/xft_futex_wait.c",
    "src/atomics/futex/linux/libc/xft_futex_wake.c",
};

const SRCS_FUTEX_win32 = [_][]const u8{
    "src/atomics/futex/win32/xft_futex_wait.c",
    "src/atomics/futex/win32/xft_futex_wake.c",
};

const SRCS_THREADS_x86_64 = [_][]const u8{
    "src/threads/linux/x86_64/xft_thread_destroy.c",
};

const SRCS_THREADS_aarch64 = [_][]const u8{
    "src/threads/linux/aarch64/xft_thread_destroy.c",
};

const SRCS_THREADS_libc = [_][]const u8{
    "src/threads/linux/libc/xft_thread_spawn.c",
    "src/threads/linux/libc/xft_thread_join.c",
    "src/threads/linux/libc/xft_thread_detach.c",
};

const SRCS_THREADS_win32 = [_][]const u8{
    "src/threads/win32/xft_thread_spawn.c",
    "src/threads/win32/xft_thread_join.c",
    "src/threads/win32/xft_thread_detach.c",
};

const SRCS_PERF = [_][]const u8{
    "subprojects/perf/src/xft_bind_process_to_cpu.c",
    "subprojects/perf/src/xft_get_flag_groups.c",
    "subprojects/perf/src/xft_perf_counter_interface.c",
    "subprojects/perf/src/xft_perf_create_counters.c",
    "subprojects/perf/src/xft_perf_destroy_counters.c",
    "subprojects/perf/src/xft_perf_sampling.c",
};

const SRCS_RT_win32 = [_][]const u8{
    "src/rt/win32/xft_kernel_ptrs_destroy.c",
    "src/rt/win32/xft_get_kernel_ptrs.c",
    "src/rt/win32/xft_get_rt.c",
    "src/rt/win32/xft_get_sysinfo.c",
    "src/rt/win32/xft_start_tls_for_main_thread.c",
};

const SRCS_XID = [_][]const u8{
    "src/xid/xft_xid_decode.c",
    "src/xid/xft_xid_is_set.c",
    "src/xid/xft_xidtable.c",
};

const SRCS_ARCH_x86_64 = [_][]const u8{
    "src/atomics/mutex/xft_mutex_backoff_x86_64.c",
    "src/arch/x86_64/xft_cache_line_size.c",
};

const SRCS_ARCH_aarch64 = [_][]const u8{
    "src/atomics/mutex/xft_mutex_backoff_aarch64.c",
    "src/arch/aarch64/xft_cache_line_size.c",
};

const SRCS_RT_ENTRY_x86_64 = [_][]const u8{
    "src/rt/linux/x86_64/xft_rt.c",
};

const SRCS_RT_ENTRY_aarch64 = [_][]const u8{
    "src/rt/linux/aarch64/xft_rt.c",
};

const SRCS_RT_ENTRY_libc = [_][]const u8{
    "src/rt/libc/xft_rt.c",
};

const SRCS_RT_ENTRY_win32 = [_][]const u8{
    "src/rt/win32/xft_rt.c",
};

const XFT_SYSCALLS = [_][]const u8{
    "clock_gettime",
    "clone",
    "close",
    "exit",
    "exit_group",
    "fmap",
    "fork",
    "getpid",
    "ioctl",
    "lockf",
    "madvise",
    "mkdir",
    "mmap",
    "mprotect",
    "mremap",
    "open",
    "perf_events",
    "prlimit64",
    "read",
    "sched_getaffinity",
    "sched_setaffinity",
    "set_tid_address",
    "statx",
    "wait4",
    "write",
    "writev",
};

fn syscallSrcs(comptime dir: []const u8, comptime names: []const []const u8) [names.len][]const u8 {
    var out: [names.len][]const u8 = undefined;
    for (names, &out) |n, *o| o.* = dir ++ "/xft_" ++ n ++ ".c";
    return out;
}

const SRCS_FREESTANDING_x86_64 = syscallSrcs("src/os/linux/x86_64", &(XFT_SYSCALLS ++ .{"set_thread_pointer"}));
const SRCS_FREESTANDING_aarch64 = syscallSrcs("src/os/linux/aarch64", &(XFT_SYSCALLS ++ .{ "syscall6", "set_thread_pointer" }));
const SRCS_LIBC = syscallSrcs("src/os/linux/libc", &XFT_SYSCALLS);

const SRCS_TEST = [_][]const u8{
    "tests/alloc/arena/arena_extend_test.c",
    "tests/alloc/arena/arena_extend_test_clean_releases.c",
    "tests/alloc/arena/arena_extend_test_rewind_grow.c",
    "tests/alloc/arena/arena_extend_test_rewind_reuse.c",
    "tests/alloc/arena/arena_extend_test_trigger.c",
    "tests/alloc/arena/arena_test.c",
    "tests/alloc/arena/arena_test_alignment.c",
    "tests/alloc/arena/arena_test_basic.c",
    "tests/alloc/arena/arena_test_checkpoint.c",
    "tests/alloc/arena/arena_test_invalid.c",
    "tests/alloc/arena/arena_test_uniq.c",
    "tests/alloc/gpa/gpa_bulk_test.c",
    "tests/alloc/gpa/gpa_bulk_test_align.c",
    "tests/alloc/gpa/gpa_bulk_test_mixed_sizes.c",
    "tests/alloc/gpa/gpa_bulk_test_mixed_sizes_fill.c",
    "tests/alloc/gpa/gpa_bulk_test_reuse.c",
    "tests/alloc/gpa/gpa_bulk_test_same_size.c",
    "tests/alloc/gpa/gpa_bulk_test_same_size_fill.c",
    "tests/alloc/vtables/vtables_test.c",
    "tests/alloc/vtables/vtables_test_arena.c",
    "tests/alloc/vtables/vtables_test_arena_realloc.c",
    "tests/alloc/vtables/vtables_test_clone.c",
    "tests/alloc/vtables/vtables_test_gpa.c",
    "tests/alloc/vtables/vtables_test_gpa_freelist.c",
    "tests/alloc/vtables/vtables_test_gpa_freelist_advance.c",
    "tests/alloc/vtables/vtables_test_gpa_realloc.c",
    "tests/alloc/vtables/vtables_test_palloc.c",
    "tests/alloc/vtables/vtables_test_palloc_realloc.c",
    "tests/bmi/bmi_test.c",
    "tests/bmi/bmi_test_bswap.c",
    "tests/bmi/bmi_test_clz.c",
    "tests/bmi/bmi_test_ctz.c",
    "tests/bmi/bmi_test_endian.c",
    "tests/bmi/bmi_test_max.c",
    "tests/bmi/vmanip/vmanip_test_native_8_a.c",
    "tests/bmi/vmanip/vmanip_test_native_8_b.c",
    "tests/bmi/vmanip/vmanip_test_native_16_a.c",
    "tests/bmi/vmanip/vmanip_test_native_16_b.c",
    "tests/bmi/vmanip/vmanip_test_native_32_a.c",
    "tests/bmi/vmanip/vmanip_test_native_32_b.c",
    "tests/bmi/vmanip/vmanip_test_native_64_a.c",
    "tests/bmi/vmanip/vmanip_test_native_64_b.c",
    "tests/bmi/vmanip/vmanip_test_128_8_a.c",
    "tests/bmi/vmanip/vmanip_test_128_8_b.c",
    "tests/bmi/vmanip/vmanip_test_256_8_a.c",
    "tests/bmi/vmanip/vmanip_test_256_8_b.c",
    "tests/bmi/vmanip/vmanip_test_512_8_a.c",
    "tests/bmi/vmanip/vmanip_test_512_8_b.c",
    "tests/bmi/vmanip/vmanip_test_128_16_a.c",
    "tests/bmi/vmanip/vmanip_test_128_16_b.c",
    "tests/bmi/vmanip/vmanip_test_256_16_a.c",
    "tests/bmi/vmanip/vmanip_test_256_16_b.c",
    "tests/bmi/vmanip/vmanip_test_512_16_a.c",
    "tests/bmi/vmanip/vmanip_test_512_16_b.c",
    "tests/bmi/vmanip/vmanip_test_128_32_a.c",
    "tests/bmi/vmanip/vmanip_test_128_32_b.c",
    "tests/bmi/vmanip/vmanip_test_256_32_a.c",
    "tests/bmi/vmanip/vmanip_test_256_32_b.c",
    "tests/bmi/vmanip/vmanip_test_512_32_a.c",
    "tests/bmi/vmanip/vmanip_test_512_32_b.c",
    "tests/bmi/vmanip/vmanip_test_128_64_a.c",
    "tests/bmi/vmanip/vmanip_test_128_64_b.c",
    "tests/bmi/vmanip/vmanip_test_256_64_a.c",
    "tests/bmi/vmanip/vmanip_test_256_64_b.c",
    "tests/bmi/vmanip/vmanip_test_512_64_a.c",
    "tests/bmi/vmanip/vmanip_test_512_64_b.c",
    "tests/bmi/vmanip/vmanip_test_fault_native_8.c",
    "tests/bmi/vmanip/vmanip_test_fault_native_16.c",
    "tests/bmi/vmanip/vmanip_test_fault_native_32.c",
    "tests/bmi/vmanip/vmanip_test_fault_native_64.c",
    "tests/bmi/vmanip/vmanip_test_fault_128_8.c",
    "tests/bmi/vmanip/vmanip_test_fault_256_8.c",
    "tests/bmi/vmanip/vmanip_test_fault_512_8.c",
    "tests/bmi/vmanip/vmanip_test_fault_128_16.c",
    "tests/bmi/vmanip/vmanip_test_fault_256_16.c",
    "tests/bmi/vmanip/vmanip_test_fault_512_16.c",
    "tests/bmi/vmanip/vmanip_test_fault_128_32.c",
    "tests/bmi/vmanip/vmanip_test_fault_256_32.c",
    "tests/bmi/vmanip/vmanip_test_fault_512_32.c",
    "tests/bmi/vmanip/vmanip_test_fault_128_64.c",
    "tests/bmi/vmanip/vmanip_test_fault_256_64.c",
    "tests/bmi/vmanip/vmanip_test_fault_512_64.c",
    "tests/bmi/vmanip/vmanip_test_utils2.c",
    "tests/bmi/vmanip/vmanip_test_utils.c",
    "tests/bmi/vmanip/vmanip_test.c",
    "tests/containers/indexmap/imap_test.c",
    "tests/containers/indexmap/imap_test_churn.c",
    "tests/containers/indexmap/imap_test_delete.c",
    "tests/containers/indexmap/imap_test_dense.c",
    "tests/containers/indexmap/imap_test_insert_lookup.c",
    "tests/containers/indexmap/imap_test_many.c",
    "tests/containers/indexmap/imap_test_overwrite.c",
    "tests/containers/indexmap/imap_test_seeded.c",
    "tests/containers/soa/soa_test.c",
    "tests/containers/soa/soa_test_append.c",
    "tests/containers/soa/soa_test_ctx.c",
    "tests/containers/soa/soa_test_grow.c",
    "tests/containers/soa/soa_test_new.c",
    "tests/containers/soa/soa_test_reserve.c",
    "tests/containers/str/str_test.c",
    "tests/containers/str/str_test_extend.c",
    "tests/containers/str/str_test_new.c",
    "tests/containers/str/str_test_push_back.c",
    "tests/containers/str/str_test_remove.c",
    "tests/containers/swissmap/map_test.c",
    "tests/containers/swissmap/map_test_churn.c",
    "tests/containers/swissmap/map_test_delete.c",
    "tests/containers/swissmap/map_test_insert_lookup.c",
    "tests/containers/swissmap/map_test_many.c",
    "tests/containers/swissmap/map_test_overwrite.c",
    "tests/containers/vec/vec_test.c",
    "tests/containers/vec/vec_test_clear_reuse.c",
    "tests/containers/vec/vec_test_extend.c",
    "tests/containers/vec/vec_test_pop.c",
    "tests/containers/vec/vec_test_push_get.c",
    "tests/cstr/cstr_to_str/cstr_to_str_test.c",
    "tests/cstr/strlen/strlen_test.c",
    "tests/cstr/strlen/strlen_test_basic.c",
    "tests/cstr/strlen/strlen_test_long.c",
    "tests/cstr/strlen/strlen_test_misaligned.c",
    "tests/hash/murmur3/murmur_test.c",
    "tests/hash/murmur3/murmur_test_deterministic.c",
    "tests/hash/murmur3/murmur_test_diff_input.c",
    "tests/hash/murmur3/murmur_test_lengths.c",
    "tests/hash/murmur3/murmur_test_seed.c",
    "tests/hash/xxh3/xxh3_test.c",
    "tests/hash/xxh3/xxh3_test_basic.c",
    "tests/hash/xxh3/xxh3_test_edge.c",
    "tests/hash/xxh3/xxh3_test_lengths.c",
    "tests/hash/xxh3/xxh3_test_lengths_large.c",
    "tests/hash/xxh3/xxh3_test_seeds.c",
    "tests/mem/bzero/bzero_test.c",
    "tests/mem/memchr/memchr_test.c",
    "tests/mem/memchr/memchr_test_basic.c",
    "tests/mem/memchr/memchr_test_edge.c",
    "tests/mem/memchr/memchr_test_long.c",
    "tests/mem/memchr/memchr_test_misaligned.c",
    "tests/mem/memcmp/memcmp_test.c",
    "tests/mem/memcmp/memcmp_test_basic.c",
    "tests/mem/memcmp/memcmp_test_binary.c",
    "tests/mem/memcmp/memcmp_test_long.c",
    "tests/mem/memcmp/memcmp_test_misaligned.c",
    "tests/mem/memcpy/memcpy_test.c",
    "tests/mem/memcpy/memcpy_test_basic.c",
    "tests/mem/memcpy/memcpy_test_large.c",
    "tests/mem/memcpy/memcpy_test_misaligned.c",
    "tests/mem/mload/mload_test.c",
    "tests/mem/memmove/memmove_test.c",
    "tests/mem/memset/memset_test.c",
    "tests/mem/memset/memset_test_basic.c",
    "tests/mem/memset/memset_test_large.c",
    "tests/mem/memset/memset_test_misaligned.c",
    "tests/mem/streaming/streaming_test.c",
    "tests/mem/streaming/streaming_test_memcpy.c",
    "tests/mem/streaming/streaming_test_memset.c",
    "tests/rng/xoshiro/xoshiro_test.c",
    "tests/rng/xoshiro/xoshiro_test_basic.c",
    "tests/rng/xoshiro/xoshiro_test_init_diff.c",
    "tests/rng/xoshiro/xoshiro_test_not_constant.c",
    "tests/rng/xoshiro/xoshiro_test_state_changes.c",
    "tests/test_state.c",
    "tests/tests_main.c",
    "tests/threads/thread_test.c",
    "tests/threads/thread_test_detach.c",
    "tests/threads/thread_test_detach_utils.c",
    "tests/threads/thread_test_join.c",
    "tests/threads/thread_test_signal.c",
    "tests/threads/thread_test_tls.c",
    "tests/xid/xid_test.c",
    "tests/xid/xid_test_ascii.c",
    "tests/xid/xid_test_exhaustive.c",
    "tests/xid/xid_test_points.c",
    "tests/xid/xid_test_table.c",
};

const SRCS_TEST_THREADS_FREESTANDING = [_][]const u8{
    "tests/freestanding_thread_tests.c",
    "tests/threads/thread_test_detach.c",
    "tests/threads/thread_test_detach_utils.c",
    "tests/threads/thread_test_join.c",
    "tests/threads/thread_test_signal.c",
    "tests/threads/thread_test_tls.c",
};

const SRCS_BENCH_memcpy_bench = [_][]const u8{
    "bench/memcpy/memcpy_bench.c",
    "bench/memcpy/memcpy_bench_large.c",
    "bench/memcpy/memcpy_bench_medium.c",
    "bench/memcpy/memcpy_bench_short.c",
    "bench/memcpy/memcpy_bench_varied.c",
};

const SRCS_BENCH_memcpy_stream_bench = [_][]const u8{
    "bench/memcpy/memcpy_stream_bench.c",
    "bench/memcpy/memcpy_bench_stream.c",
};

const SRCS_BENCH_strlen_bench = [_][]const u8{
    "bench/strlen/strlen_bench.c",
    "bench/strlen/strlen_bench_large.c",
    "bench/strlen/strlen_bench_medium.c",
    "bench/strlen/strlen_bench_short.c",
    "bench/strlen/strlen_bench_utils.c",
    "bench/strlen/strlen_bench_varied.c",
};

const SRCS_BENCH_libc_bench = [_][]const u8{
    "bench/libc/libc_bench.c",
    "bench/libc/libc_bench_run.c",
    "bench/libc/libc_memcpy_large.c",
    "bench/libc/libc_memcpy_medium.c",
    "bench/libc/libc_memcpy_short.c",
    "bench/libc/libc_memcpy_varied.c",
    "bench/libc/libc_strlen_large.c",
    "bench/libc/libc_strlen_medium.c",
    "bench/libc/libc_strlen_short.c",
    "bench/libc/libc_strlen_varied.c",
    "bench/strlen/strlen_bench_utils.c",
};

const SRCS_BENCH_memmove_bench = [_][]const u8{
    "bench/memmove/memmove_bench.c",
    "bench/memmove/memmove_bench_large.c",
    "bench/memmove/memmove_bench_medium.c",
    "bench/memmove/memmove_bench_short.c",
    "bench/memmove/memmove_bench_utils.c",
    "bench/memmove/memmove_bench_varied.c",
};

const SRCS_BENCH_memset_bench = [_][]const u8{
    "bench/memset/memset_bench.c",
    "bench/memset/memset_bench_large.c",
    "bench/memset/memset_bench_medium.c",
    "bench/memset/memset_bench_short.c",
    "bench/memset/memset_bench_varied.c",
};

const SRCS_BENCH_memset_stream_bench = [_][]const u8{
    "bench/memset/memset_stream_bench.c",
    "bench/memset/memset_bench_stream.c",
};

const SRCS_BENCH_gpa_bench = [_][]const u8{
    "bench/gpa/gpa_bench.c",
    "bench/gpa/gpa_bench_bulk.c",
    "bench/gpa/gpa_bench_get.c",
    "bench/gpa/gpa_bench_ops.c",
    "bench/gpa/gpa_bench_rand.c",
};

const SRCS_BENCH_arena_bench = [_][]const u8{
    "bench/arena/arena_bench.c",
    "bench/arena/arena_bench_ops.c",
    "bench/arena/arena_bench_rand.c",
};

const SRCS_BENCH_vec_bench = [_][]const u8{
    "bench/vec/vec_bench.c",
    "bench/vec/vec_bench_extend.c",
    "bench/vec/vec_bench_ops.c",
    "bench/vec/vec_bench_read.c",
    "bench/vec/vec_bench_remove.c",
    "bench/vec/vec_bench_state.c",
};

const SRCS_BENCH_soa_bench = [_][]const u8{
    "bench/soa/soa_bench.c",
    "bench/soa/soa_bench_append.c",
    "bench/soa/soa_bench_iter.c",
    "bench/soa/soa_bench_read.c",
    "bench/soa/soa_bench_state.c",
};

const SRCS_BENCH_swissmap_bench = [_][]const u8{
    "bench/swissmap/swissmap_bench.c",
    "bench/swissmap/swissmap_bench_insert.c",
    "bench/swissmap/swissmap_bench_large.c",
    "bench/swissmap/swissmap_bench_large_state.c",
    "bench/swissmap/swissmap_bench_lookup.c",
    "bench/swissmap/swissmap_bench_state.c",
};

const SRCS_BENCH_indexmap_bench = [_][]const u8{
    "bench/indexmap/indexmap_bench.c",
    "bench/indexmap/indexmap_bench_insert.c",
    "bench/indexmap/indexmap_bench_large.c",
    "bench/indexmap/indexmap_bench_large_state.c",
    "bench/indexmap/indexmap_bench_lookup.c",
    "bench/indexmap/indexmap_bench_state.c",
};

const SRCS_BENCH_stl_bench = [_][]const u8{
    "bench/stl/stl_bench.c",
    "bench/stl/stl_bench_run.c",
    "bench/stl/stl_bench_str_state.c",
    "bench/stl/stl_bench_swiss_str.c",
    "bench/stl/stl_bench_swiss_str_large.c",
    "bench/stl/stl_bench_swiss_str_state.c",
    "bench/stl/stl_bench_umap.cpp",
    "bench/stl/stl_bench_umap_large.cpp",
    "bench/stl/stl_bench_umap_state.cpp",
    "bench/stl/stl_bench_umap_str.cpp",
    "bench/stl/stl_bench_umap_str_large.cpp",
    "bench/stl/stl_bench_umap_str_state.cpp",
    "bench/stl/stl_bench_vector.cpp",
    "bench/stl/stl_bench_vector_access.cpp",
    "bench/swissmap/swissmap_bench_insert.c",
    "bench/swissmap/swissmap_bench_large.c",
    "bench/swissmap/swissmap_bench_large_state.c",
    "bench/swissmap/swissmap_bench_lookup.c",
    "bench/swissmap/swissmap_bench_state.c",
    "bench/vec/vec_bench_extend.c",
    "bench/vec/vec_bench_ops.c",
    "bench/vec/vec_bench_read.c",
    "bench/vec/vec_bench_remove.c",
    "bench/vec/vec_bench_state.c",
};

const SRCS_FUZZ = [_][2][]const u8{
    .{ "fuzz_mem", "fuzz/mem_fuzz.c" },
    .{ "fuzz_vec", "fuzz/vec_fuzz.c" },
    .{ "fuzz_map", "fuzz/map_fuzz.c" },
};

const SRCS_TAILOR = [_][]const u8{
    "subprojects/tailor/src/xft_tailor_bytes.c",
    "subprojects/tailor/src/xft_tailor_calibration.c",
    "subprojects/tailor/src/xft_tailor_fuzz.c",
    "subprojects/tailor/src/xft_tailor_get_rand_buffer.c",
    "subprojects/tailor/src/xft_tailor_get_random_num.c",
    "subprojects/tailor/src/xft_tailor_getcount.c",
    "subprojects/tailor/src/xft_tailor_new.c",
    "subprojects/tailor/src/xft_tailor_resample.c",
    "subprojects/tailor/src/xft_tailor_run.c",
    "subprojects/tailor/src/xft_tailor_summary.c",
    "subprojects/tailor/src/xft_tailor_top.c",
};

const SRCS_GENTABLE = [_][]const u8{
    "subprojects/gentable/src/xft_gentable_main.c",
    "subprojects/gentable/src/xft_gentable_iterate.c",
    "subprojects/gentable/src/xft_gentable_classify.c",
    "subprojects/gentable/src/xft_gentable_intern.c",
    "subprojects/gentable/src/xft_gentable_jmpline.c",
    "subprojects/gentable/src/xft_gentable_tag.c",
    "subprojects/gentable/src/xft_gentable_emit.c",
};

const BENCHES = .{
    .{ "memcpy_bench",        &SRCS_BENCH_memcpy_bench },
    .{ "memcpy_stream_bench", &SRCS_BENCH_memcpy_stream_bench },
    .{ "memmove_bench",       &SRCS_BENCH_memmove_bench },
    .{ "memset_bench",        &SRCS_BENCH_memset_bench },
    .{ "memset_stream_bench", &SRCS_BENCH_memset_stream_bench },
    .{ "strlen_bench",        &SRCS_BENCH_strlen_bench },
    .{ "gpa_bench",           &SRCS_BENCH_gpa_bench },
    .{ "arena_bench",         &SRCS_BENCH_arena_bench },
    .{ "vec_bench",           &SRCS_BENCH_vec_bench },
    .{ "soa_bench",           &SRCS_BENCH_soa_bench },
    .{ "swissmap_bench",      &SRCS_BENCH_swissmap_bench },
    .{ "indexmap_bench",      &SRCS_BENCH_indexmap_bench },
};

const INTERNAL_DIRS = [_][]const u8{
    "src/internal",
    "src/internal/linux",
};

// perf and tailor sit on perf_event_open: linux only
const SUBPROJECT_INCLUDES = [_][]const u8{
    "subprojects/perf/include",
    "subprojects/tailor/include",
};

const CFLAGS = [_][]const u8{
    "-pipe",
    "-ffunction-sections",
    "-fdata-sections",
    "-finline-functions",
    "-fvisibility=hidden",
    "-fno-common",
    "-fstrict-aliasing",
    "-g3",
};

// elf only; clang ignores them for coff
const CFLAGS_linux = [_][]const u8{
    "-fno-semantic-interposition",
};

const CFLAGS_x86_64 = [_][]const u8{
    "-fcf-protection=full",
};

const CFLAGS_HOSTED = [_][]const u8{
    "-fstack-protector-strong",
};

const CFLAGS_FREESTANDING = [_][]const u8{
    "-ffreestanding",
    "-fno-builtin",
    "-fno-stack-protector",
};

const CFLAGS_FREESTANDING_win32 = CFLAGS_FREESTANDING ++ [_][]const u8{
    "-mno-stack-arg-probe",
};

const CFLAGS_STACK_CHECK = [_][]const u8{
    "-fstack-protector-all",
    "-fstack-check",
};

// ubsan comes from sanitize_c; zig ships no asan runtime
const SAN_FLAGS = [_][]const u8{
    "-fsanitize-recover=null",
    "-fno-omit-frame-pointer",
};


const CXX_WARNS = [_][]const u8{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wshadow",
    "-Werror",
};

const WARNS = [_][]const u8{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wstrict-aliasing",
    "-Wshadow",
    "-Waddress",
    "-Wattributes",
    "-Wredundant-decls",
    "-Wstrict-prototypes",
    "-Wmissing-prototypes",
    "-Wold-style-definition",
    "-Wnull-dereference",
    "-Wundef",
    "-Wformat-security",
    "-Wformat=2",
    "-Wformat-nonliteral",
    "-Wwrite-strings",
    "-Wuninitialized",
    "-Wpointer-arith",
    "-Wunused",
    "-Wtautological-compare",
    "-Wvla",
    "-Wignored-qualifiers",
    "-Wnonnull",
    "-Winfinite-recursion",
    "-Wimplicit",
    "-Wimplicit-fallthrough",
    "-Wmissing-braces",
    "-Wmissing-include-dirs",
    "-Wparentheses",
    "-Wshift-negative-value",
    "-Wmisleading-indentation",
    "-Wfloat-equal",
    "-Wdangling-else",
    "-Wmissing-noreturn",
    "-Wchar-subscripts",
    "-Wsequence-point",
    "-Wbool-operation",
    "-Wunreachable-code",
    "-Wformat-overflow",
    "-Wformat-truncation",
    "-Wcast-function-type",
    "-Wbitwise-instead-of-logical",
    "-Wnull-pointer-arithmetic",
    "-Wcast-function-type-strict",
    "-Wambiguous-ellipsis",
    "-Wambiguous-macro",
    "-Wassume",
    "-Wpessimizing-move",
    "-Wgnu-union-cast",
    "-Wlanguage-extension-token",
    "-Wgnu-statement-expression-from-macro-expansion",
    "-Wbounds-safety-counted-by-elt-type-unknown-size",
    "-Wcast-function-type-mismatch",
    "-Wc99-compat",
    "-Wbool-conversions",
    "-Wbitfield-enum-conversion",
    "-Warray-bounds-pointer-arithmetic",
    "-Wloop-analysis",
    "-Wcomma",
    "-Wover-aligned",
    "-Wconditional-uninitialized",
    "-Wimplicit-float-conversion",
    "-Wimplicit-int-conversion",
    "-Wshorten-64-to-32",
    "-Wstring-concatenation",
    "-Wunused-but-set-parameter",
    "-Wsizeof-array-div",
    "-Wtautological-constant-in-range-compare",
    "-Wno-extra-semi-stmt",
    "-Wno-static-in-inline",
    "-Wthread-safety",
    "-Wdangling",
    "-Werror",
};

const xft_config = struct {
    use_libc:   bool,
    sanitize:   bool,
    lto:        bool,
    fast_math:  bool,
    benches:    bool,
    tests:      bool,
    fuzz:       bool,
    bootstrap:  bool,
    llc:        u64,
};

const xft_ctx = struct {
    b:      *std.Build,
    target: std.Build.ResolvedTarget,
    opt:    std.lang.Optimize,
    cfg:    xft_config,
};

const xft_variant = struct {
    name:       []const u8,
    lib:        *std.Build.Step.Compile,
    perf:       ?*std.Build.Step.Compile = null,
    tailor:     ?*std.Build.Step.Compile = null,
    libc:       bool,
    sanitize:   bool,
    lto:        bool,
};

fn isWin32(x: xft_ctx) bool {
    return x.target.result.os.tag == .windows;
}

fn hasStackClash(x: xft_ctx) bool {
    return switch (x.target.result.cpu.arch) {
        .x86, .x86_64, .aarch64, .aarch64_be, .riscv32, .riscv64,
        .powerpc, .powerpc64, .powerpc64le, .s390x, .loongarch64 => true,
        else => false,
    };
}

fn hasFreestandingThreads(x: xft_ctx) bool {
    return x.target.result.os.tag == .linux and switch (x.target.result.cpu.arch) {
        .x86_64, .aarch64 => true,
        else => false,
    };
}

fn hasStackCheck(x: xft_ctx) bool {
    return x.target.result.cpu.arch != .x86;
}

fn cflags(x: xft_ctx, v: xft_variant, cxx: bool) ![]const []const u8 {
    const a = x.b.allocator;
    var flags: std.ArrayList([]const u8) = .empty;
    try flags.append(a, if (cxx) "-std=gnu++23" else "-std=gnu23");
    try flags.appendSlice(a, &CFLAGS);
    if (!isWin32(x))
        try flags.appendSlice(a, &CFLAGS_linux);
    if (!isWin32(x) and hasStackClash(x))
        try flags.append(a, "-fstack-clash-protection");
    if (x.target.result.cpu.arch == .x86_64)
        try flags.appendSlice(a, &CFLAGS_x86_64);
    if (x.cfg.fast_math)
        try flags.append(a, "-ffast-math");
    if (x.opt == .fast or x.opt == .safe)
        try flags.append(a, "-O3");
    try flags.appendSlice(a, if (cxx) &CXX_WARNS else &WARNS);

    if (v.libc) {
        try flags.appendSlice(a, &CFLAGS_HOSTED);
    } else if (isWin32(x)) {
        try flags.appendSlice(a, &CFLAGS_FREESTANDING_win32);
    } else {
        try flags.appendSlice(a, &CFLAGS_FREESTANDING);
    }
    if (v.sanitize) {
        try flags.appendSlice(a, &SAN_FLAGS);
        try flags.appendSlice(a, &CFLAGS_STACK_CHECK);
    }
    return flags.items;
}

fn xftModule(x: xft_ctx, v: xft_variant) *std.Build.Module {
    const b = x.b;
    const mod = b.createModule(.{
        .target = x.target,
        .optimize = x.opt,
        .link_libc = v.libc,
        .stack_protector = v.libc,
        .stack_check = v.sanitize and hasStackCheck(x),
        .sanitize_c = if (v.sanitize) .full else .off,
        .omit_frame_pointer = !v.sanitize,
        .no_builtin = if (v.libc) null else true,
    });
    mod.addIncludePath(b.path("include"));
    for (INTERNAL_DIRS) |d| mod.addIncludePath(b.path(d));
    if (!isWin32(x))
        for (SUBPROJECT_INCLUDES) |d| mod.addIncludePath(b.path(d));
    mod.addCMacro("XFT_LLC", b.fmt("{d}", .{x.cfg.llc}));
    mod.addCMacro("XFT_LLC_SIZE", b.fmt("{d}ULL", .{x.cfg.llc}));
    if (v.libc) {
        mod.addCMacro("XFT_REQUIRE_LIBC", "1");
        if (!isWin32(x)) mod.addCMacro("_GNU_SOURCE", "1");
    }
    if (isWin32(x)) {
        if (!v.libc)
            mod.addSystemIncludePath(std.Build.LazyPath.zig_lib.path(b, "libc/include/any-windows-any"));
        mod.linkSystemLibrary("kernel32", .{});
        mod.linkSystemLibrary("shell32", .{});
        mod.linkSystemLibrary("bcrypt", .{});
        mod.linkSystemLibrary("api-ms-win-core-synch-l1-2-0", .{});
    }
    return mod;
}

fn addSrcs(x: xft_ctx, mod: *std.Build.Module, v: xft_variant, files: []const []const u8) !void {
    mod.addCSourceFiles(.{
        .files = files,
        .flags = try cflags(x, v, false),
        .language = .c,
    });
}

fn addXft(x: xft_ctx, name: []const u8, libc: bool, sanitize: bool) !xft_variant {
    var v: xft_variant = .{
        .name = name,
        .lib = undefined,
        .libc = libc or sanitize,
        .sanitize = sanitize,
        .lto = x.cfg.lto and !sanitize,
    };
    const mod = xftModule(x, v);
    try addSrcs(x, mod, v, &SRCS);
    if (!x.cfg.bootstrap)
        try addSrcs(x, mod, v, &SRCS_XID);
    try addSrcs(x, mod, v, &SRCS_ARCH_x86_64);
    try addSrcs(x, mod, v, &SRCS_ARCH_aarch64);
    if (isWin32(x)) {
        try addSrcs(x, mod, v, &SRCS_RT_win32);
        try addSrcs(x, mod, v, &SRCS_THREADS_win32);
        try addSrcs(x, mod, v, &SRCS_FUTEX_win32);
        try addSrcs(x, mod, v, if (v.libc) &SRCS_RT_ENTRY_libc else &SRCS_RT_ENTRY_win32);
    } else if (v.libc) {
        try addSrcs(x, mod, v, &SRCS_RT_linux);
        try addSrcs(x, mod, v, &SRCS_LIBC);
        try addSrcs(x, mod, v, &SRCS_RT_ENTRY_libc);
        try addSrcs(x, mod, v, &SRCS_THREADS_libc);
        try addSrcs(x, mod, v, &SRCS_FUTEX_libc);
    } else {
        try addSrcs(x, mod, v, &SRCS_RT_linux);
        try addSrcs(x, mod, v, &SRCS_FREESTANDING_x86_64);
        try addSrcs(x, mod, v, &SRCS_RT_ENTRY_x86_64);
        try addSrcs(x, mod, v, &SRCS_FREESTANDING_aarch64);
        try addSrcs(x, mod, v, &SRCS_RT_ENTRY_aarch64);
        try addSrcs(x, mod, v, &SRCS_THREADS_linux);
        try addSrcs(x, mod, v, &SRCS_THREADS_x86_64);
        try addSrcs(x, mod, v, &SRCS_THREADS_aarch64);
        try addSrcs(x, mod, v, &SRCS_FUTEX_x86_64);
        try addSrcs(x, mod, v, &SRCS_FUTEX_aarch64);
    }
    v.lib = x.b.addLibrary(.{
        .linkage = .static,
        .use_llvm = true,
        .use_lld = true,
        .name = name,
        .root_module = mod,
    });
    if (v.lto) v.lib.lto = .full;
    if (!isWin32(x)) {
        v.perf = try addSubproject(x, v, "perf", &SRCS_PERF);
        v.tailor = try addSubproject(x, v, "tailor", &SRCS_TAILOR);
        v.lib.root_module.linkLibrary(v.perf.?);
        v.lib.root_module.linkLibrary(v.tailor.?);
    }
    return v;
}

fn addSubproject(x: xft_ctx, v: xft_variant, name: []const u8, files: []const []const u8) !*std.Build.Step.Compile {
    const b = x.b;
    const mod = xftModule(x, v);
    mod.addIncludePath(b.path(b.fmt("subprojects/{s}/src/internal", .{name})));
    try addSrcs(x, mod, v, files);

    const lib = b.addLibrary(.{
        .linkage = .static,
        .use_llvm = true,
        .use_lld = true,
        .name = b.fmt("{s}-{s}", .{ v.name, name }),
        .root_module = mod,
    });
    if (v.lto) lib.lto = .full;
    return lib;
}

fn addHarness(x: xft_ctx, name: []const u8, v: xft_variant, files: []const []const u8, includes: []const []const u8, extra: []const []const u8) !*std.Build.Step.Compile {
    const b = x.b;
    const a = b.allocator;
    const mod = xftModule(x, v);
    for (includes) |d| mod.addIncludePath(b.path(d));
    mod.linkLibrary(v.lib);
    var c_files: std.ArrayList([]const u8) = .empty;
    var cxx_files: std.ArrayList([]const u8) = .empty;
    for (files) |f| {
        if (std.mem.endsWith(u8, f, ".cpp")) {
            try cxx_files.append(a, f);
        } else {
            try c_files.append(a, f);
        }
    }
    var flags: std.ArrayList([]const u8) = .empty;
    try flags.appendSlice(a, try cflags(x, v, false));
    try flags.appendSlice(a, extra);
    mod.addCSourceFiles(.{ .files = c_files.items, .flags = flags.items, .language = .c });
    if (cxx_files.items.len != 0) {
        mod.link_libcpp = true;
        mod.addCSourceFiles(.{ .files = cxx_files.items, .flags = try cflags(x, v, true), .language = .cpp });
    }
    const exe = b.addExecutable(.{
        .name = name,
        .use_llvm = true,
        .use_lld = true,
        .root_module = mod,
    });
    if (!v.libc and isWin32(x)) exe.entry = .{ .symbol_name = "_start" };
    if (v.lto) exe.lto = .full;
    b.installArtifact(exe);
    return exe;
}

pub fn build(b: *std.Build) !void {
    const opt = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});

    const cfg: xft_config =
    .{
        .use_libc     = b.option(bool, "use-libc",  "Link against libc")                  orelse false,
        .sanitize     = b.option(bool, "sanitize",  "Enable sanitizers")                  orelse false,
        .lto          = b.option(bool, "lto",       "Enable link-time optimization")      orelse false,
        .fast_math    = b.option(bool, "fast-math", "-ffast-math")                        orelse false,
        .benches      = b.option(bool, "benches",   "Build benchmarks")                   orelse false,
        .tests        = b.option(bool, "tests",     "Build tests")                        orelse false,
        .fuzz         = b.option(bool, "fuzz",      "Build fuzz targets")                 orelse false,
        .bootstrap    = b.option(bool, "bootstrap", "Build xft without xid and regenerate its table") orelse false,
        .llc           = b.option(u64,  "llc",       "Last level cache size in bytes")     orelse 16777216,
    };

    if (cfg.sanitize and cfg.use_libc == false)         return error.CannotCompileSanitizedWithoutLibc;
    if (cfg.fuzz and (!cfg.sanitize or !cfg.use_libc))  return error.CannotCompileFuzzerWithoutSanitizer;
    if (cfg.benches and cfg.sanitize)                   return error.CannotBenchmarkWithSanitizers;
    if (cfg.benches and opt != .fast)                   return error.CannotBenchmarkWithDebug;
    if (cfg.benches and target.result.os.tag != .linux) return error.CannotBenchmarkOutsideLinux;
    if (cfg.bootstrap and cfg.tests)                    return error.CannotTestWithoutXid;
    if (cfg.bootstrap)
        std.Io.Dir.cwd().access(b.graph.io, try b.root.joinString(b.allocator, "DerivedCoreProperties.txt"), .{}) catch
            return error.MissingDerivedCoreProperties;

    const x: xft_ctx = .{ .b = b, .target = target, .opt = opt, .cfg = cfg };

    const xft = try addXft(x, "xft", cfg.use_libc, cfg.sanitize);
    xft.lib.installHeadersDirectory(b.path("include"), "", .{});
    b.installArtifact(xft.lib);
    if (xft.perf) |perf| {
        perf.installHeadersDirectory(b.path("subprojects/perf/include"), "", .{});
        xft.lib.installLibraryHeaders(perf);
        b.installArtifact(perf);
    }
    if (xft.tailor) |tailor| {
        tailor.installHeadersDirectory(b.path("subprojects/tailor/include"), "", .{});
        xft.lib.installLibraryHeaders(tailor);
        b.installArtifact(tailor);
    }
    if (cfg.bootstrap) {
        const gentable = try addHarness(x, "gentable", xft, &SRCS_GENTABLE, &.{"subprojects/gentable/include"}, &.{});
        const run = b.addRunArtifact(gentable);
        run.setCwd(b.path("."));
        run.addFileArg(b.path("DerivedCoreProperties.txt"));
        const xid_table = b.step("xid-table", "Regenerate src/xid/xft_xidtable.c");
        xid_table.dependOn(&run.step);
        b.getInstallStep().dependOn(xid_table);
    }
    if (cfg.tests or cfg.fuzz) {
        const san = if (cfg.sanitize) xft else try addXft(x, "xft-san", true, true);
        if (cfg.tests) {
            const tests = try addHarness(x, "tests", san, &SRCS_TEST, &.{"tests/include"}, &.{});
            const run = b.addRunArtifact(tests);
            const test_step = b.step("test", "Run the unit tests");
            test_step.dependOn(&run.step);
            if (hasFreestandingThreads(x)) {
                const freestanding = if (xft.libc) try addXft(x, "xft-freestanding", false, false) else xft;
                const thread_tests = try addHarness(x, "freestanding_thread_tests", freestanding, &SRCS_TEST_THREADS_FREESTANDING, &.{"tests/include"}, &.{});
                const run_thread_tests = b.addRunArtifact(thread_tests);
                b.step("freestanding-thread-tests", "Run the thread tests against the freestanding build").dependOn(&run_thread_tests.step);
                test_step.dependOn(&run_thread_tests.step);
            }
        }
        if (cfg.fuzz) {
            const fuzz = b.step("fuzz", "Run the fuzz targets");
            for (SRCS_FUZZ) |f| {
                const exe = try addHarness(x, f[0], san, &.{f[1]}, &.{"fuzz"}, &.{});
                fuzz.dependOn(&b.addRunArtifact(exe).step);
            }
        }
    }

    if (cfg.benches) {
        const hosted = if (cfg.use_libc) xft else try addXft(x, "xft-libc", true, false);

        const run_bench = b.step("run-bench", "Run the benchmarks");
        inline for (BENCHES) |bench| {
            const exe = try addHarness(x, bench[0], xft, bench[1], &.{"bench/include"}, &.{});
            run_bench.dependOn(&b.addRunArtifact(exe).step);
        }
        const libc_bench = try addHarness(x, "libc_bench", hosted, &SRCS_BENCH_libc_bench, &.{"bench/include"}, &.{"-fno-builtin"});
        run_bench.dependOn(&b.addRunArtifact(libc_bench).step);
        const stl_bench = try addHarness(x, "stl_bench", hosted, &SRCS_BENCH_stl_bench, &.{"bench/include"}, &.{});
        run_bench.dependOn(&b.addRunArtifact(stl_bench).step);
    }
}
