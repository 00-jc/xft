/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_ash.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:52:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 16:54:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_ASH_H
# define FT_P_ASH_H

# include "ash.h"

/*
** The arch ash itself was compiled for. Kept as a macro so the getter
** body stays free of preprocessor branches.
*/

# if defined(__x86_64__)
#  define FT_COMPILER_ARCH X86_64
# elif defined(__aarch64__)
#  define FT_COMPILER_ARCH AARCH64
# else
#  define FT_COMPILER_ARCH OTHER
# endif

/*
** Per-toolchain flag sets, modelled on the portage env profiles:
** clang -> /etc/portage/env/clang.conf, gcc -> /etc/portage/env/gcc.conf,
** link  -> /etc/portage/env/ld-lld.conf (and ld-mold.conf, same body).
**
** Only the optimization domain lives here: -march/-mtune belong to
** ft_ash_conf_cpu, the guards to ft_ash_conf_stack_check,
** -ffreestanding/-nostdlib to ft_ash_conf_runtime and every -flto
** spelling to ft_ash_conf_lto.
*/

/*
** Diagnostics. Every pass reports on bs->stderr_w before handing a KO back
** up the chain, so a failed conf reads bottom-up: the flag that could not
** be pushed, the pass that owned it, then the group.
*/

void			ft__ash_slice(t_u64 *values, const char *str)\
					__attribute__((__nonnull__(1, 2)));

void			ft__ash_log(t_ash *bs, const char *msg)\
					__attribute__((__nonnull__(1, 2)));

t_result		ft__ash_ko(t_ash *bs, const char *msg)\
					__attribute__((__nonnull__(1, 2)));

t_result		ft__ash_ko_flag(t_ash *bs, const char *msg,\
					const char *flag)\
					__attribute__((__nonnull__(1, 2, 3)));

/*
** Verbose pre-invocation dump on bs->stdout_w: the resolved toolchain path,
** then one line per flag already in bs->flags. Deliberately never touches
** bs->files/bs->objs - no file or object name is printed.
*/

void			ft__ash_print_invocation(t_ash *bs, const char *toolchain)\
					__attribute__((__nonnull__(1, 2)));

/*
** Progress lines, always naming the source(s) a spawn consumes rather than
** what it produces: ft__ash_log_step is the compile loop's one-per-source
** "<compiler> -> <file.c>", ft__ash_log_files is the archive/link
** "<ar|driver> -> <file.c> <file.c> ..." for the single spawn that takes
** them all. Buffered like every other stdout write: nothing here flushes,
** ft_ash_runner drains bs->stdout_w once on its way out.
*/

void			ft__ash_log_step(t_ash *bs, const char *tool,\
					const char *target)\
					__attribute__((__nonnull__(1, 2, 3)));

void			ft__ash_log_files(t_ash *bs, const char *tool)\
					__attribute__((__nonnull__(1, 2)));

const char		*ft__ash_lto_flag(const t_ash *bs)\
					__attribute__((__nonnull__(1), pure));

/*
** Phase one of the runner: name every object and make every directory
** they imply, before any compiler runs. Leaves bs->objs complete and
** index-aligned with files, and leaves the names in one contiguous run
** at the bottom of the arena so the compile pass only ever checkpoints
** around argv.
*/

t_result		ft__ash_populate_obj_soa(t_ash *bs)\
					__attribute__((__nonnull__(1)));

/*
** Second half of phase one: bs->objs is already fully named, so this walks
** each obj's path and mkdirs every '/'-delimited prefix in order. mkdir's
** -1 return can't tell "already exists" from a real failure (see the
** syscalls gotcha in CLAUDE.md), so each prefix is probed with ft_stat
** first and only mkdir'd if the stat fails.
*/

t_result		ft__ash_mkdir_p(t_ash *bs)\
					__attribute__((__nonnull__(1)));

/*
** Hardcoded, absolute candidate paths per toolchain: ft_execve does no
** PATH search, so the compiler binary needs an absolute path from
** somewhere. Each list is null-terminated; every getter stats its own
** candidates and returns the first one that exists, or nullptr if none
** do. ft__ash_get_toolchain_hardcoded just picks the list for
** bs->opts.toolchain and forwards that probe result.
*/

const char		*ft__ash_get_gcc(void);
const char		*ft__ash_get_clang(void);
const char		*ft__ash_get_zig(void);
const char		*ft__ash_get_toolchain_hardcoded(t_compiler compiler);

t_result		ft__ash_get_toolchain(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

/*
** Same probe shape for the archiver. It has to match the compiler rather
** than the linker: an ARCHIVE built with LTO holds bitcode members and
** only that toolchain's ar can index them. zig ships llvm's, so ZIG_CC
** shares the clang answer.
*/

const char		*ft__ash_get_llvm_ar(void);
const char		*ft__ash_get_gcc_ar(void);
const char		*ft__ash_get_archiver_hardcoded(t_compiler compiler);

t_result		ft__ash_get_archiver(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

/*
** The linker is probed but never spawned: the link step runs the compiler
** driver and lets -fuse-ld= (ft_ash_conf_linker) select one. The probe is
** there so a missing linker is reported by name here instead of surfacing
** as an opaque driver failure.
*/

const char		*ft__ash_get_bfd(void);
const char		*ft__ash_get_lld(void);
const char		*ft__ash_get_mold(void);
const char		*ft__ash_get_linker_hardcoded(t_linker linker);

t_result		ft__ash_get_linker(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

t_result		ft__ash_rip_it_clang(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		ft__ash_rip_it_gcc(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		ft__ash_link_opt(t_ash *bs)\
					__attribute__((__nonnull__(1)));

/*
** Builds one compiler invocation's argv template: TOOLCHAIN + bs->flags +
** "-c" + file + "-o" + obj + nullptr, allocated out of bs->arena. Built
** once; *file_slot points at the `file` slot so a per-file loop can just
** overwrite file_slot[0] and file_slot[2] (the obj slot) instead of
** rebuilding argv per file. ft__ash_run_build below drives that loop.
*/

t_result		ft__ash_build_argv(t_ash *bs, const char *toolchain,
					char ***argv, char ***file_slot)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

/*
** Drives argv's compile loop: fork + execve + wait4 per bs->files entry,
** overwriting file_slot[0] (source) and file_slot[2] (obj, past the
** constant "-o") in place instead of rebuilding argv each time. Requires
** bs->rt to already be populated (envp comes from it).
*/

t_result		ft__ash_run_build(t_ash *bs, const char *toolchain,
					char **argv, char **file_slot)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

/*
** One fork + execve + wait4, shared by the compile loop and the link
** phase. `label` only ever names the failure (the source file, or the
** artifact). Requires bs->rt: envp comes from it.
*/

t_result		ft__ash_spawn(t_ash *bs, const char *path,\
					char **argv, const char *label)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

/*
** Phase three: one spawn that turns bs->objs into bs->final_artifact.
** ARCHIVE runs the archiver directly; EXE/SHARED_OBJ run the compiler
** driver with the ldflags (which is where -fuse-ld= lives), never ld.
** Both argv builders allocate out of bs->arena and borrow every string.
*/

t_result		ft__ash_build_ar_argv(t_ash *bs, const char *archiver,\
					char ***argv)\
					__attribute__((__nonnull__(1, 2, 3)));

t_result		ft__ash_build_link_argv(t_ash *bs, const char *driver,\
					char ***argv)\
					__attribute__((__nonnull__(1, 2, 3)));

t_result		ft__ash_link(t_ash *bs)\
					__attribute__((__nonnull__(1)));

#endif
