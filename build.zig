// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   build.zig                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/05/15 07:20:25 by jaicastr          #+#    #+#             //
//   Updated: 2026/05/20 15:31:00 by jaicastr         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
const std = @import("std");

const NAME       = "xft";
const OBJDIR     = "build";
const INCLUDES   = "include";

const WARNS_COMMON = &[_][]const u8{
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wpedantic",
    "-std=c23",
    "-fstrict-aliasing",
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
    "-Wdouble-promotion",
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
    "-Wthread-safety",
    "-Wdangling",
};

const CFLAGS_COMMON = &[_][]const u8{
    "-D_GNU_SOURCE",
    "-pipe",
    "-ffunction-sections",
    "-fdata-sections",
    "-finline-functions",
    "-fvisibility=hidden",
    "-fstack-protector-strong",
    "-fcf-protection=full",
    "-ftrivial-auto-var-init=zero",
    "-fno-common",
    "-fstack-clash-protection",
    "-fslp-vectorize",
    "-ftree-slp-vectorize",
    "-ftree-vectorize",
    "-fvectorize",
    "-g3",
} ++ WARNS_COMMON;

const SRCS_ALLOC = &[_][]const u8{
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

const SRCS_CSTR = &[_][]const u8{
    "src/cstr/ft_strlen.c",
    "src/cstr/ft_cstr_to_str.c",
};

const SRCS_CTYPE = &[_][]const u8{
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

const SRCS_SYSCALLS = &[_][]const u8{
    "src/syscalls/ft_write.c",
    "src/syscalls/ft_read.c",
    "src/syscalls/ft_fmap.c",
    "src/syscalls/ft_mremap.c",
    "src/syscalls/ft_lockf.c",
    "src/syscalls/ft_mmap.c",
    "src/syscalls/ft_stat.c",
};

const SRCS_IO = &[_][]const u8{
    "src/io/ft_printf_helpers2.c",
    "src/io/ft_read_file_portable.c",
    "src/io/ft_read_file.c",
    "src/io/ft_printf_helpers.c",
    "src/io/ft_printf.c",
};

const SRCS_MATH = &[_][]const u8{
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

const SRCS_MEM = &[_][]const u8{
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
    "src/mem/ft_memfence.c",
};

const SRCS_THREADPOOL = &[_][]const u8{
    "src/threadpool/ft_threadpool.c",
    "src/threadpool/ft_threadpool_wait.c",
};

const SRCS_VEC = &[_][]const u8{
    "src/vec/ft_vec_remove.c",
    "src/vec/ft_vec_pop.c",
    "src/vec/ft_vec.c",
    "src/vec/ft_vec_free.c",
    "src/vec/ft_vec_push_back.c",
    "src/vec/ft_vec_get.c",
    "src/vec/ft_vec_bytesize.c",
    "src/vec/ft_vec_extend.c",
};

const SRCS_STR = &[_][]const u8{
    "src/str/ft_str.c",
    "src/str/ft_str_extend.c",
    "src/str/ft_str_push_back.c",
    "src/str/ft_str_remove.c",
};

const SRCS_BMI = &[_][]const u8{
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

const SRCS_HASH = &[_][]const u8{
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

const SRCS_ENV = &[_][]const u8{
    "src/env/ft_getenv.c",
};

const SRCS_MAP = &[_][]const u8{
    "src/swissmap/ft_map_insert.c",
    "src/swissmap/ft_map_lookup.c",
    "src/swissmap/ft_map_delete.c",
    "src/swissmap/ft_map_rehash.c",
    "src/swissmap/ft_map_insert_unchecked.c",
    "src/swissmap/ft_map.c",
};

const SRCS_HINT = &[_][]const u8{
    "src/hint/ft_pin_invariant.c",
    "src/hint/ft_assume.c",
    "src/hint/ft_hardcrash.c",
};

const SRCS_TOK = &[_][]const u8{
    "src/tokenizer/ft_eat_u128.c",
    "src/tokenizer/ft_eat_u256.c",
    "src/tokenizer/ft_eat_u512.c",
    "src/tokenizer/ft_eat_until.c",
    "src/tokenizer/ft_eat_u8.c",
    "src/tokenizer/ft_sets.c",
    "src/tokenizer/ft_tokenizer.c",
    "src/tokenizer/ft_eat_while.c",
};

const SRCS_TIME = &[_][]const u8{
    "src/time/ft_get_nanos.c",
};

const SRCS_RNG = &[_][]const u8{
    "src/rng/ft_xoshiro256ss.c",
};

const SRCS_PERF = &[_][]const u8{
    "src/perf/ft_perf_create_counters.c",
    "src/perf/ft_bind_process_to_cpu.c",
    "src/perf/ft_get_flag_groups.c",
    "src/perf/ft_perf_counter_interface.c",
    "src/perf/ft_perf_destroy_counters.c",
    "src/perf/ft_perf_sampling.c",
};

const SRCS_SORT = &[_][]const u8{
    "src/sort/ft_qsort.c",
    "src/sort/ft_qsort_u64s.c",
};

const SRCS_TAILOR = &[_][]const u8{
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

const SRCS_BENCH = &[_][]const u8{
    "bench/memcpy/memcpy_bench_large.c",
    "bench/memcpy/memcpy_bench_varied.c",
    "bench/memcpy/memcpy_bench_medium.c",
    "bench/memcpy/memcpy_bench_short.c",
    "bench/memcpy/memcpy_bench.c",
};

const SRCS_FUZZ = &[_][]const u8{
    "src/fuzzer/ft_fuzzer_get_rand.c",
    "src/fuzzer/ft_fuzzer_initrand.c",
    "src/fuzzer/ft_fuzzer.c",
};

const MODULES = SRCS_SYSCALLS
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
                ++ SRCS_ENV
                ++ SRCS_MAP
                ++ SRCS_HINT
                ++ SRCS_TOK
                ++ SRCS_THREADPOOL
                ++ SRCS_TIME
                ++ SRCS_PERF
                ++ SRCS_RNG
                ++ SRCS_TAILOR
                ++ SRCS_SORT
                ++ SRCS_FUZZ;

const Opts = struct 
{
    target:   std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
};

const SRCS_TEST = &[_][2][]const u8{
    .{ "tests/memchr_test.c",        "test_memchr" },
    .{ "tests/strlen_test.c",        "test_strlen" },
    .{ "tests/memcmp_test.c",        "test_memcmp" },
    .{ "tests/memcpy_test.c",        "test_memcpy" },
    .{ "tests/memset_test.c",        "test_memset" },
    .{ "tests/streaming_mem_test.c", "test_streaming_mem" },
    .{ "tests/vec_test.c",           "test_vec" },
    .{ "tests/str_test.c",           "test_str" },
    .{ "tests/cstr_test.c",          "test_cstr" },
    .{ "tests/map_test.c",           "test_map" },
    .{ "tests/murmur_test.c",        "test_murmur" },
    .{ "tests/bmi_test.c",           "test_bmi" },
    .{ "tests/xxh3_test.c",          "test_xxh3" },
    .{ "tests/arena_test.c",         "test_arena" },
    .{ "tests/arena_extend_test.c",  "test_arena_extend" },
    .{ "tests/test_vtables.c",       "test_vtables" },
    .{ "tests/gpa_bulk_test.c",      "test_gpa_bulk" },
};
 
const SRCS_FUZZ_TARGETS = &[_][2][]const u8{
    .{ "fuzz/mem_fuzz.c", "fuzz_mem" },
    .{ "fuzz/vec_fuzz.c", "fuzz_vec" },
    .{ "fuzz/map_fuzz.c", "fuzz_map" },
};

const SRCS_BENCH_MEMCPY = &[_][]const u8{
    "bench/memcpy/memcpy_bench.c",
    "bench/memcpy/memcpy_bench_large.c",
    "bench/memcpy/memcpy_bench_medium.c",
    "bench/memcpy/memcpy_bench_short.c",
    "bench/memcpy/memcpy_bench_varied.c",
};

const SRCS_BENCH_MEMCPY_STREAM = &[_][]const u8{
    "bench/memcpy/memcpy_stream_bench.c",
    "bench/memcpy/memcpy_bench_stream.c",
};

const SRCS_BENCH_MEMMOVE = &[_][]const u8{
    "bench/memmove/memmove_bench.c",
    "bench/memmove/memmove_bench_large.c",
    "bench/memmove/memmove_bench_medium.c",
    "bench/memmove/memmove_bench_short.c",
    "bench/memmove/memmove_bench_utils.c",
    "bench/memmove/memmove_bench_varied.c",
};

const SRCS_BENCH_MEMSET = &[_][]const u8{
    "bench/memset/memset_bench.c",
    "bench/memset/memset_bench_large.c",
    "bench/memset/memset_bench_medium.c",
    "bench/memset/memset_bench_short.c",
    "bench/memset/memset_bench_varied.c",
};

const SRCS_BENCH_MEMSET_STREAM = &[_][]const u8{
    "bench/memset/memset_stream_bench.c",
    "bench/memset/memset_bench_stream.c",
};

const SRCS_BENCH_GPA = &[_][]const u8{
    "bench/gpa/gpa_bench.c",
    "bench/gpa/gpa_bench_get.c",
    "bench/gpa/gpa_bench_ops.c",
    "bench/gpa/gpa_bench_rand.c",
    "bench/gpa/gpa_bench_bulk.c",
};

const SRCS_BENCH_ARENA = &[_][]const u8{
    "bench/arena/arena_bench.c",
    "bench/arena/arena_bench_ops.c",
    "bench/arena/arena_bench_rand.c",
};

const BENCH_TARGETS = &[_]struct { name: []const u8, srcs: []const []const u8 }{
    .{ .name = "memcpy_bench",        .srcs = SRCS_BENCH_MEMCPY },
    .{ .name = "memcpy_stream_bench", .srcs = SRCS_BENCH_MEMCPY_STREAM },
    .{ .name = "memmove_bench",       .srcs = SRCS_BENCH_MEMMOVE },
    .{ .name = "memset_bench",        .srcs = SRCS_BENCH_MEMSET },
    .{ .name = "memset_stream_bench", .srcs = SRCS_BENCH_MEMSET_STREAM },
    .{ .name = "gpa_bench",           .srcs = SRCS_BENCH_GPA },
    .{ .name = "arena_bench",         .srcs = SRCS_BENCH_ARENA },
};

const XFT = struct {
    lto:  bool,
    san:  bool,
    tsan: bool,
};

inline fn make_lib(
    b:              *std.Build,
    comptime cfg:   XFT,
    opt:            Opts,
) *std.Build.Step.Compile
{
    var mod = b.createModule(.{
        .optimize        = if (cfg.san) .Debug else opt.optimize,
        .target          = opt.target,
        .link_libc       = true,
        .dwarf_format    = .@"64",
        .stack_check     = true,
        .stack_protector = true,
        .error_tracing   = false,
        .red_zone        = if (cfg.san) true else false,  
        .sanitize_c      = if (cfg.san)  .full else .off,
        .sanitize_thread = cfg.tsan,
        .single_threaded = false,
    });
    mod.addIncludePath(b.path(INCLUDES));
    mod.addCSourceFiles(.{
        .files = MODULES,
        .flags = CFLAGS_COMMON
    });
    const lib = b.addLibrary(.{
        .name        = NAME,
        .linkage     = .static,
        .root_module = mod,
        .use_llvm    = true,
        .use_lld     = true,
    });

    if (cfg.san) lib.bundle_ubsan_rt = true;
    lib.link_data_sections     = true;
    lib.link_function_sections = true;
    lib.link_z_relro           = true;
    lib.link_z_lazy            = false;
    lib.lto                    = if (cfg.lto and !cfg.san) .full else .none;
    return lib;
}

inline fn make_test_exe(
    b:        *std.Build,
    opt:      Opts,
    xft_san:  *std.Build.Step.Compile,
    name:     []const u8,
    src_path: []const u8,
) *std.Build.Step.Compile
{
    var mod = b.createModule(.{
        .optimize        = .Debug,
        .target          = opt.target,
        .link_libc       = true,
        .sanitize_c      = .full,
        .single_threaded = false,
    });
    mod.addIncludePath(b.path(INCLUDES));
    mod.addCSourceFiles(.{
        .files = &.{src_path},
        .flags = CFLAGS_COMMON,
    });
    mod.linkLibrary(xft_san);
    const exe = b.addExecutable(.{
        .name        = name,
        .root_module = mod,
        .use_llvm    = true,
        .use_lld     = true,
    });
    exe.bundle_ubsan_rt = true;
    return exe;
}
 
pub fn build(b: *std.Build) !void
{

    var io_th = std.Io.Threaded.init(b.allocator, .{});
    defer io_th.deinit();
    const io = io_th.io();
    const opts = Opts{
        .target   = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    };

    const llc_cmd = try std.process.run(b.allocator, io, .{.argv = &.{"getconf", "LEVEL3_CACHE_SIZE"}});
    const llc_trim = std.mem.trim(u8, llc_cmd.stdout, &std.ascii.whitespace);
    const llc_out = try std.fmt.parseInt(usize, llc_trim, 10);

    const xft           = make_lib(b, .{.tsan = false, .san = false, .lto = true  }, opts);
    const xft_san       = make_lib(b, .{.tsan = false, .san = true,  .lto = false }, opts);
    const xft_tsan      = make_lib(b, .{.tsan = true,  .san = false, .lto = false }, opts);
    const xft_no_lto    = make_lib(b, .{.tsan = false, .san = false, .lto = false }, opts);

    b.step("core", "Build the core lib").dependOn(&b.addInstallArtifact(xft, .{}).step);
    b.step("san",  "Build with sanitizers").dependOn(&b.addInstallArtifact(xft_san, .{}).step);
    b.step("tsan", "Build with thread sanitizer").dependOn(&b.addInstallArtifact(xft_tsan, .{}).step);
    b.step("nolto","Build with no lto").dependOn(&b.addInstallArtifact(xft_no_lto, .{}).step);

    const test_step = b.step("test", "Build and run tests (sanitized)");
    inline for (SRCS_TEST) |t|
    {
        const exe = make_test_exe(b, opts, xft_san, t[1], t[0]);
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        test_step.dependOn(&run.step);
    }
    const fuzz_step = b.step("fuzz", "Build and run fuzz targets (sanitized)");
    inline for (SRCS_FUZZ_TARGETS) |t| {
        const exe = make_test_exe(b, opts, xft_san, t[1], t[0]);
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        fuzz_step.dependOn(&run.step);
    }
    const bench_step = b.step("bench", "Build and run benchmarks");
    inline for (BENCH_TARGETS) |t| {
        var mod = b.createModule(.{
            .optimize        = .ReleaseFast,
            .target          = opts.target,
            .link_libc       = true,
            .single_threaded = false,
        });
        mod.addIncludePath(b.path(INCLUDES));
        mod.addIncludePath(b.path("bench/include"));
        mod.addCMacro("FT_NTHREADS", b.fmt("{d}", .{std.Thread.getCpuCount() catch 1}));
        mod.addCMacro("FT_LLC", b.fmt("{d}", .{llc_out}));
        mod.addCSourceFiles(.{
            .files = t.srcs,
            .flags = CFLAGS_COMMON ++ .{"-march=native", "-mtune=native", "-O3"},
        });
        mod.linkLibrary(xft);
        const exe = b.addExecutable(.{
            .name        = t.name,
            .root_module = mod,
            .use_llvm    = true,
            .use_lld     = true,
        });
        exe.link_data_sections     = true;
        exe.link_function_sections = true;
        exe.link_z_relro           = true;
        exe.link_z_lazy            = false;
        exe.lto                    = .full;
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        bench_step.dependOn(&run.step);
    }
    const analyze_step = b.step("analyze", "Run clang static analyzer");
    const analyze_cmd = b.addSystemCommand(
        .{"clang"} ++ CFLAGS_COMMON ++ .{ "--analyze", "--analyzer-output", "text", "-I", INCLUDES } ++ MODULES,
    );
    analyze_step.dependOn(&analyze_cmd.step);
}
