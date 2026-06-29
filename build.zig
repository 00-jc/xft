// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   build.zig                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/05/15 07:20:25 by jaicastr          #+#    #+#             //
//   Updated: 2026/06/29 09:39:36 by username         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

const std           = @import("std");
const builtin       = @import("builtin");

const NAME              = "xft";
const INCLUDES          = "include";
const MODULES           = @import("bs/sources.zig").MODULES;
const SRCS_TEST         = @import("bs/sources.zig").SRCS_TEST;
const SRCS_FUZZ_TARGETS = @import("bs/sources.zig").SRCS_FUZZ_TARGETS;
const BENCH_TARGETS     = @import("bs/sources.zig").BENCH_TARGETS;
const CFLAGS_COMMON     = @import("bs/flags.zig").CFLAGS_COMMON;

pub const Opts = struct
{
    target:   std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    use_libc: bool,
    llc_out:  usize,
};

const XFT = struct {
    lto:  bool,
    san:  bool,
    tsan: bool,
};

const LIB_STEPS = &[_]struct { step: []const u8, desc: []const u8, cfg: XFT }{
    .{ .step = "tsan",  .desc = "Build with thread sanitizer", .cfg = .{ .lto = false, .san = false, .tsan = true  } },
    .{ .step = "nolto", .desc = "Build with no lto",           .cfg = .{ .lto = false, .san = false, .tsan = false } },
};

inline fn add_includes(b: *std.Build, mod: *std.Build.Module) void
{
    mod.addIncludePath(b.path(INCLUDES));
    mod.addSystemIncludePath(.{ .cwd_relative = "/usr/include" });
}

inline fn install_step(
    b:    *std.Build,
    name: []const u8,
    desc: []const u8,
    lib:  *std.Build.Step.Compile,
) void
{
    b.step(name, desc).dependOn(&b.addInstallArtifact(lib, .{}).step);
}

inline fn make_lib(
    b:              *std.Build,
    comptime cfg:   XFT,
    opt:            Opts,
) *std.Build.Step.Compile
{
    const libc = cfg.san or builtin.cpu.arch != .x86_64 or opt.use_libc;
    var mod = b.createModule(.{
        .optimize        = if (cfg.san or cfg.tsan) .Debug else opt.optimize,
        .target          = opt.target,
        .link_libc       = libc,
        .dwarf_format    = .@"64",
        .stack_check     = libc, // stack checking is only available with libc
        .stack_protector = libc,
        .error_tracing   = false,
        .red_zone        = cfg.san,
        .sanitize_c      = if (cfg.san or cfg.tsan) .full else .off,
        .sanitize_thread = cfg.tsan,
        .pic             = true,
    });
    add_includes(b, mod);
    mod.addCMacro("FT_NTHREADS", b.fmt("{d}", .{std.Thread.getCpuCount() catch 1}));
    mod.addCMacro("FT_LLC", b.fmt("{d}", .{opt.llc_out}));
    if (libc) mod.addCMacro("FT_REQUIRE_LIBC", "");
    mod.addCSourceFiles(.{
        .files = MODULES,
        .flags = CFLAGS_COMMON,
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
        .single_threaded = true,
        .sanitize_c      = .full,
        .stack_protector = true,
        .stack_check     = true,
    });
    add_includes(b, mod);
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

inline fn make_bench_exe(
    b:         *std.Build,
    opt:       Opts,
    xft_bench: *std.Build.Step.Compile,
    name:      []const u8,
    srcs:      []const []const u8,
) *std.Build.Step.Compile
{
    var mod = b.createModule(.{
        .optimize        = .ReleaseFast,
        .target          = opt.target,
        .link_libc       = builtin.cpu.arch != .x86_64,
        .single_threaded = false,
    });
    add_includes(b, mod);
    mod.addIncludePath(b.path("bench/include"));
    mod.addCMacro("FT_LLC", b.fmt("{d}", .{opt.llc_out}));
    mod.addCSourceFiles(.{
        .files = srcs,
        .flags = CFLAGS_COMMON ++ .{ "-march=native", "-mtune=native", "-O3" },
    });
    if (mod.link_libc) |x| if (x) mod.addCMacro("FT_REQUIRE_LIBC", "");
    mod.linkLibrary(xft_bench);
    const exe = b.addExecutable(.{
        .name        = name,
        .root_module = mod,
        .use_llvm    = true,
        .use_lld     = true,
    });
    exe.link_gc_sections       = true;
    exe.link_data_sections     = true;
    exe.link_function_sections = true;
    exe.link_z_relro           = true;
    exe.link_z_lazy            = false;
    exe.lto                    = .full;
    return exe;
}

pub fn build(b: *std.Build) !void
{
    var io_th = std.Io.Threaded.init(b.allocator, .{});
    defer io_th.deinit();
    const io = io_th.io();

    const llc_cmd  = try std.process.run(b.allocator, io, .{ .argv = &.{ "getconf", "LEVEL3_CACHE_SIZE" } });
    const llc_trim = std.mem.trim(u8, llc_cmd.stdout, &std.ascii.whitespace);
    const llc_out  = try std.fmt.parseInt(usize, llc_trim, 10);

    const opts = Opts
    {
        .target   = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
        .use_libc = b.option(bool, "libc", "Link against libc") orelse false,
        .llc_out  = llc_out,
    };

    const xft     = make_lib(b, .{ .tsan = false, .san = false, .lto = true  }, opts);
    const xft_san = make_lib(b, .{ .tsan = false, .san = true,  .lto = false }, opts);

    const xft_bench = make_lib(b, .{ .tsan = false, .san = false, .lto = true }, opts);

    install_step(b, "core", "Build the core lib", xft);
    install_step(b, "san",  "Build with sanitizers", xft_san);
    inline for (LIB_STEPS) |v|
        install_step(b, v.step, v.desc, make_lib(b, v.cfg, opts));

    const test_step = b.step("test", "Build and run tests (sanitized)");
    inline for (SRCS_TEST) |t|
    {
        const exe = make_test_exe(b, opts, xft_san, t[1], t[0]);
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        test_step.dependOn(&run.step);
    }

    const fuzz_step = b.step("fuzz", "Build and run fuzz targets (sanitized)");
    inline for (SRCS_FUZZ_TARGETS) |t|
    {
        const exe = make_test_exe(b, opts, xft_san, t[1], t[0]);
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        fuzz_step.dependOn(&run.step);
    }

    const bench_step = b.step("bench", "Build and run benchmarks");
    inline for (BENCH_TARGETS) |t|
    {
        const exe = make_bench_exe(b, opts, xft_bench, t.name, t.srcs);
        const run = b.addRunArtifact(exe);
        run.has_side_effects = true;
        bench_step.dependOn(&run.step);
    }

    const analyze_step = b.step("analyze", "Run clang static analyzer");
    const analyze_cmd  = b.addSystemCommand(
        .{"clang"} ++ CFLAGS_COMMON ++ .{ "--analyze", "--analyzer-output", "text", "-I", INCLUDES } ++ MODULES,
    );
    analyze_step.dependOn(&analyze_cmd.step);
    const complexity_cmd = b.addSystemCommand(
        .{"complexity"} ++ .{ "--threshold", "0", "--horrid", "10", "--histogram" } ++ MODULES,
    );
    const norminette = b.addSystemCommand(&.{"norminette"});

    const lint_step = b.step("lint", "lint code and enforce formatting");
    lint_step.dependOn(&complexity_cmd.step);
    lint_step.dependOn(&norminette.step);

    b.installArtifact(xft);
}
