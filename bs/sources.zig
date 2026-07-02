// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sources.zig                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: username <your@mail.com>                   +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/06/29 09:15:56 by username          #+#    #+#             //
//   Updated: 2026/07/02 14:14:46 by jaicastr         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

const std       = @import("std");
const builtin   = @import("builtin");

pub const SRCS_ALLOC = &[_][]const u8{
    "src/alloc/ft_alloc_clone.c",
    "src/alloc/huge_matcher/ft_huge_matcher.c",
    "src/alloc/page_allocator/ft_palloc.c",
    "src/alloc/page_allocator/ft_palloc_vtable.c",
    "src/alloc/arena/ft_arena_alloc_utils.c",
    "src/alloc/arena/ft_arena_alloc_scopes.c",
    "src/alloc/arena/ft_arena_alloc.c",
    "src/alloc/arena/ft_arena_vtable.c",
    "src/alloc/gpa/ft_gpa.c",
    "src/alloc/gpa/ft_gpa_alloc.c",
    "src/alloc/gpa/ft_gpa_free.c",
    "src/alloc/gpa/ft_gpa_realloc.c",
    "src/alloc/gpa/ft_gpa_vtable.c",
    "src/alloc/report/ft_report.c",
    "src/alloc/report/ft_report_alloc.c",
    "src/alloc/report/ft_report_free.c",
    "src/alloc/report/ft_report_realloc.c",
    "src/alloc/report/ft_report_vtable.c",
};

pub const SRCS_CSTR = &[_][]const u8{
    "src/cstr/ft_strlen.c",
    "src/cstr/ft_cstr_to_str.c",
};

pub const SRCS_CTYPE = &[_][]const u8{
    "src/ctype/asm/ft_isalnum.c",
    "src/ctype/asm/ft_isalpha.c",
    "src/ctype/asm/ft_isascii.c",
    "src/ctype/asm/ft_isdigit.c",
    "src/ctype/asm/ft_isprint.c",
    "src/ctype/asm/ft_isxdigit.c",
    "src/ctype/asm/ft_isspace.c",
    "src/ctype/ft_isascii.c",
    "src/ctype/ft_isalnum.c",
    "src/ctype/ft_isprint.c",
    "src/ctype/ft_isxdigit.c",
    "src/ctype/ft_isspace.c",
    "src/ctype/ft_isalpha.c",
    "src/ctype/ft_isdigit.c",
};

pub const SRCS_SYSCALLS = &[_][]const u8{
    "src/syscalls/ft_open.c",
    "src/syscalls/ft_close.c",
    "src/syscalls/ft_clock_gettime.c",
    "src/syscalls/ft_mremap.c",
    "src/syscalls/ft_mmap.c",
    "src/syscalls/ft_fmap.c",
    "src/syscalls/ft_read.c",
    "src/syscalls/ft_write.c",
    "src/syscalls/ft_writev.c",
    "src/syscalls/ft_stat.c",
    "src/syscalls/ft_lockf.c",
    "src/syscalls/ft_exit.c",
    "src/syscalls/ft_ioctl.c",
    "src/syscalls/ft_perf_events.c",
    "src/syscalls/ft_getpid.c",
    "src/syscalls/ft_sched_setaffinity.c",
};

pub const SRCS_FMT = &[_][]const u8{
    "src/fmt/ft_fmt_handle_double.c",
    "src/fmt/ft_fmt_handle_hex.c",
    "src/fmt/ft_fmt_handle_unsigned.c",
    "src/fmt/ft_fmt_handle_signed.c",
    "src/fmt/fmt.c",
    "src/fmt/ft_fmt_handle_slice.c",
};

pub const SRCS_IO = &[_][]const u8{
    "src/io/ft_writer_write.c",
    "src/io/ft_get_fixed_fd.c",
    "src/io/blocking_fd/ft_drain.c",
    "src/io/blocking_fd/ft_flush.c",
    "src/io/blocking_fd/ft_vtable.c",
    "src/io/blocking_fd/ft_fill.c",
    "src/io/ft_reader_read.c",
};

pub const SRCS_MATH = &[_][]const u8{
    "src/math/3d/ft_3dadd.c",
    "src/math/3d/ft_3dsub.c",
    "src/math/3d/ft_3dnorm.c",
    "src/math/3d/ft_3dunit.c",
    "src/math/3d/ft_3dmul.c",
    "src/math/3d/ft_3ddiv.c",
    "src/math/3d/ft_3ddot.c",
    "src/math/3d/ft_3dcross.c",
    "src/math/ft_pow.c",
    "src/math/ft_round.c",
    "src/math/ft_fabs.c",
    "src/math/ft_sqrt.c",
    "src/math/ft_pow_signed.c",
    "src/math/ft_q_sqrt.c",
    "src/math/ft_rsqrt.c",
    "src/math/ft_drsqrt_xn.c",
    "src/math/ft_sqrt_xn.c",
};

pub const SRCS_MEM = &[_][]const u8{
    "src/mem/ft_membroadcast.c",
    "src/mem/ft_memtake.c",
    "src/mem/arch/ft_memcpy.c",
    "src/mem/arch/ft_memset.c",
    "src/mem/arch/ft_memchr.c",
    "src/mem/arch/ft_memcmp.c",
    "src/mem/arch/ft_memmove.c",
    "src/mem/ft_bzero.c",
    "src/mem/portable/ft_memcpy.c",
    "src/mem/portable/ft_memset.c",
    "src/mem/vec128/ft_memcpy.c",
    "src/mem/vec128/ft_memset.c",
    "src/mem/vec128/ft_memcmp.c",
    "src/mem/vec128/ft_memchr.c",
    "src/mem/ft_prefetch_noop.c",
    "src/mem/vec512/ft_memcpy_vec512.c",
    "src/mem/vec512/ft_memset_vec512.c",
    "src/mem/vec512/ft_memcmp_vec512.c",
    "src/mem/vec512/ft_memchr_vec512.c",
    "src/mem/ft_overlap.c",
    "src/mem/ft_fatptr.c",
    "src/mem/ft_movs.c",
    "src/mem/ft_align.c",
    "src/mem/vec256/ft_memcpy_vec256.c",
    "src/mem/vec256/ft_memset_vec256.c",
    "src/mem/vec256/ft_memcmp_vec256.c",
    "src/mem/vec256/ft_memchr_vec256.c",
    "src/mem/hugebranches/ft_memcpy_huge.c",
    "src/mem/hugebranches/ft_memmove_huge.c",
    "src/mem/hugebranches/ft_memset_huge.c",
    "src/mem/streaming/ft_memcpy_streaming.c",
    "src/mem/streaming/ft_memset_streaming.c",
    "src/mem/ft_prefetch_intrin.c",
    "src/mem/ft_stfence.c",
    "src/mem/ft_ldfence.c",
};

pub const SRCS_VEC = &[_][]const u8{
    "src/containers/vec/ft_vec_remove.c",
    "src/containers/vec/ft_vec_pop.c",
    "src/containers/vec/ft_vec.c",
    "src/containers/vec/ft_vec_free.c",
    "src/containers/vec/ft_vec_push_back.c",
    "src/containers/vec/ft_vec_get.c",
    "src/containers/vec/ft_vec_bytesize.c",
    "src/containers/vec/ft_vec_extend.c",
};

pub const SRCS_STR = &[_][]const u8{
    "src/containers/str/ft_str.c",
    "src/containers/str/ft_str_extend.c",
    "src/containers/str/ft_str_push_back.c",
    "src/containers/str/ft_str_remove.c",
};

pub const SRCS_BMI = &[_][]const u8{
    "src/bmi/__populate.c",
    "src/bmi/ft_bswap.c",
    "src/bmi/ft_rotl.c",
    "src/bmi/asm/ft_bswap_asm.c",
    "src/bmi/asm/ft_memctz_asm.c",
    "src/bmi/asm/ft_memclz_asm.c",
    "src/bmi/asm/ft_get128.c",
    "src/bmi/asm/ft_get256.c",
    "src/bmi/asm/ft_get512.c",
    "src/bmi/asm/ft_bitpack.c",
    "src/bmi/asm/ft_bitpack_intrin.c",
    "src/bmi/ft_to_be_from_be.c",
    "src/bmi/ft_to_be_from_le.c",
    "src/bmi/ft_rollmask.c",
    "src/bmi/ft_memctz.c",
    "src/bmi/ft_memclz.c",
    "src/bmi/ft_tern.c",
    "src/bmi/__maxs.c",
    "src/bmi/__max.c",
    "src/bmi/__hasz.c",
    "src/bmi/ft_next_pow2.c",
};

pub const SRCS_HASH = &[_][]const u8{
    "src/hash/murmur3/ft_murmur3.c",
    "src/hash/murmur3/ft_murmur_helpers.c",
    "src/hash/xxh3/ft_xxh3_medium_sizes.c",
    "src/hash/xxh3/ft_xxh3_large_sizes.c",
    "src/hash/xxh3/ft_xxh3_secret.c",
    "src/hash/xxh3/ft_xxh3.c",
    "src/hash/xxh3/ft_xxh3_small_sizes.c",
    "src/hash/xxh3/ft_xxh3_finalizers.c",
    "src/hash/xxh3/ft_xxh3_mul128_fold64.c",
    "src/hash/xxh3/ft_xxh3_avalanche.c",
    "src/hash/xxh3/ft_xxh3_xorshift.c",
    "src/hash/xxh3/ft_xxh3_rrmxmx.c",
};

pub const SRCS_RT = &[_][]const u8{
    "src/rt/ft_rt.c",
};

pub const SRCS_MAP = &[_][]const u8{
    "src/containers/swissmap/ft_map_insert.c",
    "src/containers/swissmap/ft_map_lookup.c",
    "src/containers/swissmap/ft_map_delete.c",
    "src/containers/swissmap/ft_map_rehash.c",
    "src/containers/swissmap/ft_map_insert_unchecked.c",
    "src/containers/swissmap/ft_map.c",
};

pub const SRCS_HINT = &[_][]const u8{
    "src/hint/ft_pin_invariant.c",
    "src/hint/ft_assume.c",
    "src/hint/ft_hardcrash.c",
};

pub const SRCS_TOK = &[_][]const u8{
    "src/containers/tokenizer/ft_eat_u128.c",
    "src/containers/tokenizer/ft_eat_u256.c",
    "src/containers/tokenizer/ft_eat_u512.c",
    "src/containers/tokenizer/ft_eat_until.c",
    "src/containers/tokenizer/ft_eat_u8.c",
    "src/containers/tokenizer/ft_sets.c",
    "src/containers/tokenizer/ft_tokenizer.c",
    "src/containers/tokenizer/ft_eat_while.c",
};

pub const SRCS_TIME = &[_][]const u8{
    "src/time/ft_get_nanos.c",
    "src/time/ft_rdtsc.c",
};

pub const SRCS_RNG = &[_][]const u8{
    "src/rng/ft_xoshiro256ss.c",
};

pub const SRCS_PERF = &[_][]const u8{
    "src/perf/ft_perf_create_counters.c",
    "src/perf/ft_bind_process_to_cpu.c",
    "src/perf/ft_get_flag_groups.c",
    "src/perf/ft_perf_counter_interface.c",
    "src/perf/ft_perf_destroy_counters.c",
    "src/perf/ft_perf_sampling.c",
};

pub const SRCS_SORT = &[_][]const u8{
    "src/sort/ft_qsort.c",
    "src/sort/ft_qsort_u64s.c",
};

pub const SRCS_TAILOR = &[_][]const u8{
    "src/tailor/ft_tailor_resample.c",
    "src/tailor/ft_tailor_fuzz.c",
    "src/tailor/ft_tailor_get_rand_buffer.c",
    "src/tailor/ft_tailor_get_random_num.c",
    "src/tailor/ft_tailor_new.c",
    "src/tailor/ft_tailor_calibration.c",
    "src/tailor/ft_tailor_summary.c",
    "src/tailor/ft_tailor_bytes.c",
    "src/tailor/ft_tailor_run.c",
    "src/tailor/ft_tailor_getcount.c",
    "src/tailor/ft_tailor_top.c",
};

pub const SRCS_BENCH = &[_][]const u8{
    "bench/memcpy/memcpy_bench_large.c",
    "bench/memcpy/memcpy_bench_varied.c",
    "bench/memcpy/memcpy_bench_medium.c",
    "bench/memcpy/memcpy_bench_short.c",
    "bench/memcpy/memcpy_bench.c",
};

pub const SRCS_FUZZ = &[_][]const u8{
    "src/fuzzer/ft_fuzzer_get_rand.c",
    "src/fuzzer/ft_fuzzer_initrand.c",
    "src/fuzzer/ft_fuzzer.c",
};

pub const MODULES = SRCS_SYSCALLS
                ++ SRCS_ALLOC
                ++ SRCS_CSTR
                ++ SRCS_CTYPE
                ++ SRCS_IO
                ++ SRCS_MATH
                ++ SRCS_MEM
                ++ SRCS_HASH
                ++ SRCS_VEC
                ++ SRCS_STR
                ++ SRCS_BMI
                ++ SRCS_RT
                ++ SRCS_MAP
                ++ SRCS_HINT
                ++ SRCS_TOK
                ++ SRCS_TIME
                ++ SRCS_PERF
                ++ SRCS_RNG
                ++ SRCS_TAILOR
                ++ SRCS_SORT
                ++ SRCS_FMT
                ++ SRCS_FUZZ;

pub const TEST_NAME = "tests";

pub const SRCS_TEST = &[_][]const u8{
    "tests/alloc/arena/arena_extend_test.c",
    "tests/alloc/arena/arena_extend_test_clean_releases.c",
    "tests/alloc/arena/arena_extend_test_rewind_grow.c",
    "tests/alloc/arena/arena_extend_test_rewind_reuse.c",
    "tests/alloc/arena/arena_extend_test_trigger.c",
    "tests/alloc/arena/arena_test_alignment.c",
    "tests/alloc/arena/arena_test_basic.c",
    "tests/alloc/arena/arena_test_uniq.c",
    "tests/alloc/arena/arena_test.c",
    "tests/alloc/arena/arena_test_checkpoint.c",
    "tests/alloc/arena/arena_test_invalid.c",
    "tests/alloc/gpa/gpa_bulk_test.c",
    "tests/alloc/gpa/gpa_bulk_test_mixed_sizes.c",
    "tests/alloc/gpa/gpa_bulk_test_mixed_sizes_fill.c",
    "tests/alloc/gpa/gpa_bulk_test_reuse.c",
    "tests/alloc/gpa/gpa_bulk_test_same_size.c",
    "tests/alloc/gpa/gpa_bulk_test_same_size_fill.c",
    "tests/alloc/vtables/vtables_test_arena.c",
    "tests/alloc/vtables/vtables_test_arena_realloc.c",
    "tests/alloc/vtables/vtables_test.c",
    "tests/alloc/vtables/vtables_test_gpa.c",
    "tests/alloc/vtables/vtables_test_gpa_realloc.c",
    "tests/alloc/vtables/vtables_test_gpa_freelist.c",
    "tests/alloc/vtables/vtables_test_gpa_freelist_advance.c",
    "tests/alloc/vtables/vtables_test_palloc.c",
    "tests/alloc/vtables/vtables_test_palloc_realloc.c",
    "tests/bmi/bmi_test_bswap.c",
    "tests/bmi/bmi_test.c",
    "tests/bmi/bmi_test_clz.c",
    "tests/bmi/bmi_test_ctz.c",
    "tests/bmi/bmi_test_max.c",
    "tests/containers/str/str_test.c",
    "tests/containers/str/str_test_extend.c",
    "tests/containers/str/str_test_new.c",
    "tests/containers/str/str_test_push_back.c",
    "tests/containers/str/str_test_remove.c",
    "tests/containers/swissmap/map_test.c",
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
    "tests/cstr/strlen/strlen_test_basic.c",
    "tests/cstr/strlen/strlen_test.c",
    "tests/cstr/strlen/strlen_test_long.c",
    "tests/cstr/strlen/strlen_test_misaligned.c",
    "tests/hash/murmur3/murmur_test.c",
    "tests/hash/murmur3/murmur_test_deterministic.c",
    "tests/hash/murmur3/murmur_test_diff_input.c",
    "tests/hash/murmur3/murmur_test_lengths.c",
    "tests/hash/murmur3/murmur_test_seed.c",
    "tests/hash/xxh3/xxh3_test_basic.c",
    "tests/hash/xxh3/xxh3_test.c",
    "tests/hash/xxh3/xxh3_test_edge.c",
    "tests/hash/xxh3/xxh3_test_lengths.c",
    "tests/hash/xxh3/xxh3_test_lengths_large.c",
    "tests/hash/xxh3/xxh3_test_seeds.c",
    "tests/mem/bzero/bzero_test.c",
    "tests/mem/memchr/memchr_test_basic.c",
    "tests/mem/memchr/memchr_test.c",
    "tests/mem/memchr/memchr_test_edge.c",
    "tests/mem/memchr/memchr_test_long.c",
    "tests/mem/memchr/memchr_test_misaligned.c",
    "tests/mem/memcmp/memcmp_test_basic.c",
    "tests/mem/memcmp/memcmp_test_binary.c",
    "tests/mem/memcmp/memcmp_test.c",
    "tests/mem/memcmp/memcmp_test_long.c",
    "tests/mem/memcmp/memcmp_test_misaligned.c",
    "tests/mem/memcpy/memcpy_test_basic.c",
    "tests/mem/memcpy/memcpy_test.c",
    "tests/mem/memcpy/memcpy_test_large.c",
    "tests/mem/memcpy/memcpy_test_misaligned.c",
    "tests/mem/memmove/memmove_test.c",
    "tests/mem/memset/memset_test_basic.c",
    "tests/mem/memset/memset_test.c",
    "tests/mem/memset/memset_test_large.c",
    "tests/mem/memset/memset_test_misaligned.c",
    "tests/mem/streaming/streaming_test.c",
    "tests/mem/streaming/streaming_test_memcpy.c",
    "tests/mem/streaming/streaming_test_memset.c",
    "tests/rng/xoshiro/xoshiro_test_basic.c",
    "tests/rng/xoshiro/xoshiro_test.c",
    "tests/rng/xoshiro/xoshiro_test_init_diff.c",
    "tests/rng/xoshiro/xoshiro_test_not_constant.c",
    "tests/rng/xoshiro/xoshiro_test_state_changes.c",
    "tests/test_state.c",
    "tests/tests_main.c",
};

pub const SRCS_FUZZ_TARGETS = &[_][2][]const u8{
    .{ "fuzz/mem_fuzz.c", "fuzz_mem" },
    .{ "fuzz/vec_fuzz.c", "fuzz_vec" },
    .{ "fuzz/map_fuzz.c", "fuzz_map" },
};

pub const SRCS_BENCH_MEMCPY = &[_][]const u8{
    "bench/memcpy/memcpy_bench.c",
    "bench/memcpy/memcpy_bench_large.c",
    "bench/memcpy/memcpy_bench_medium.c",
    "bench/memcpy/memcpy_bench_short.c",
    "bench/memcpy/memcpy_bench_varied.c",
};

pub const SRCS_BENCH_MEMCPY_STREAM = &[_][]const u8{
    "bench/memcpy/memcpy_stream_bench.c",
    "bench/memcpy/memcpy_bench_stream.c",
};

pub const SRCS_BENCH_MEMMOVE = &[_][]const u8{
    "bench/memmove/memmove_bench.c",
    "bench/memmove/memmove_bench_large.c",
    "bench/memmove/memmove_bench_medium.c",
    "bench/memmove/memmove_bench_short.c",
    "bench/memmove/memmove_bench_utils.c",
    "bench/memmove/memmove_bench_varied.c",
};

pub const SRCS_BENCH_MEMSET = &[_][]const u8{
    "bench/memset/memset_bench.c",
    "bench/memset/memset_bench_large.c",
    "bench/memset/memset_bench_medium.c",
    "bench/memset/memset_bench_short.c",
    "bench/memset/memset_bench_varied.c",
};

pub const SRCS_BENCH_MEMSET_STREAM = &[_][]const u8{
    "bench/memset/memset_stream_bench.c",
    "bench/memset/memset_bench_stream.c",
};

pub const SRCS_BENCH_GPA = &[_][]const u8{
    "bench/gpa/gpa_bench.c",
    "bench/gpa/gpa_bench_get.c",
    "bench/gpa/gpa_bench_ops.c",
    "bench/gpa/gpa_bench_rand.c",
    "bench/gpa/gpa_bench_bulk.c",
};

pub const SRCS_BENCH_ARENA = &[_][]const u8{
    "bench/arena/arena_bench.c",
    "bench/arena/arena_bench_ops.c",
    "bench/arena/arena_bench_rand.c",
};

pub const SRCS_BENCH_VEC = &[_][]const u8{
    "bench/vec/vec_bench.c",
    "bench/vec/vec_bench_state.c",
    "bench/vec/vec_bench_ops.c",
    "bench/vec/vec_bench_read.c",
    "bench/vec/vec_bench_extend.c",
    "bench/vec/vec_bench_remove.c",
};

pub const BENCH_TARGETS = &[_]struct { name: []const u8, srcs: []const []const u8 }{
    .{ .name = "vec_bench",           .srcs = SRCS_BENCH_VEC },
    .{ .name = "memcpy_bench",        .srcs = SRCS_BENCH_MEMCPY },
    .{ .name = "memcpy_stream_bench", .srcs = SRCS_BENCH_MEMCPY_STREAM },
    .{ .name = "memmove_bench",       .srcs = SRCS_BENCH_MEMMOVE },
    .{ .name = "memset_bench",        .srcs = SRCS_BENCH_MEMSET },
    .{ .name = "memset_stream_bench", .srcs = SRCS_BENCH_MEMSET_STREAM },
    .{ .name = "gpa_bench",           .srcs = SRCS_BENCH_GPA },
    .{ .name = "arena_bench",         .srcs = SRCS_BENCH_ARENA },
};
