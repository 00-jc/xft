/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ash.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:59:21 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 18:13:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASH_H
# define ASH_H

# include "alloc/arena_alloc.h"
# include "primitives.h"
# include "rt.h"
# include "alloc.h"
# include "vec.h"

# define FT_ASH_NFLAGS		64ULL
# define FT_ASH_NLDFLAGS	16ULL
# define FT_ASH_NOBJS		128ULL

typedef enum e_compiler
{
	CLANG,
	GCC,
	ZIG_CC
}	t_compiler;

typedef enum e_linker
{
	BFD,
	LLD,
	MOLD,
}	t_linker;

typedef enum e_runtime
{
	LIBC,
	FREESTANDING,
}	t_runtime;

typedef enum e_cpu
{
	NATIVE,
	GENERIC_ISA,
}	t_cpu;

typedef enum e_arch
{
	X86_64,
	AARCH64,
	OTHER,
}	t_arch;

typedef enum e_stack_check
{
	NO_STACK_CHECK,
	STACK_CHECK,
}	t_stack_check;

typedef enum e_optimize
{
	NONE,
	MEDIUM,
	HARD,
	RIP_IT,
}	t_optimize;

typedef enum e_sanitize
{
	NO_SAN,
	SAN,
}	t_sanitize;

typedef enum e_lto
{
	NO_LTO,
	THIN,
	FULL,
}	t_lto;

typedef enum e_build_type
{
	SHARED_OBJ,
	ARCHIVE,
	EXE,
}	t_build_type;

typedef struct s_ash_opts
{
	t_compiler			toolchain;
	t_linker			linker;
	t_runtime			runtime;
	t_cpu				cpu;
	t_arch				arch;
	t_stack_check		stack_check;
	t_optimize			opt_level;
	t_lto				lto;
	t_sanitize			sanitize;
	t_build_type		build_type;
	bool				force_rebuild;
}	t_ash_opts;

# ifdef __clang__

typedef struct s_array2d
{
	t_size										len;
	char *__attribute__	((counted_by(len)))		*arr;
}	t_array2d;

typedef struct s_array2d_soa
{
	t_size										len_arr;
	t_size										*len;
	char *__attribute__	((counted_by(len_arr)))	*arr;
}	t_array2d_soa;

# else

typedef struct s_array2d
{
	t_size	len;
	char	**arr;
}	t_array2d;

typedef struct s_array2d_soa
{
	t_size	len_arr;
	t_size	*len;
	char	**arr;
}	t_array2d_soa;

# endif

typedef struct s_ash_soa
{
	t_size	nentries;
	t_size	*sizes;
	t_u8	*strs;
}	t_ash_soa;

typedef struct s_ash
{
	t_xft_rt			*rt;
	t_writer			*stdout_w;
	t_writer			*stderr_w;
	t_allocator			gpa;
	t_allocator			arena;
	t_ash_opts			opts;
	t_vec				flags;
	t_vec				ldflags;
	t_buffer			build_dir;
	t_buffer			final_artifact;
	t_array2d_soa		objs;
	t_array2d_soa		files;
	t_arena_checkpoint	arena_chkp;
}	t_ash;

t_array2d		ft_ash_array2d(char **flags, t_size nflags)\
					__attribute__((const));

t_result		ft_ash_append_flags(t_ash *bs,\
					t_array2d set)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_append_flag(t_ash *bs,\
					char *flag)\
					__attribute__((__nonnull__(1, 2)));
t_result		ft_ash_append_ldflags(t_ash *bs,\
					t_array2d set)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_append_ldflag(t_ash *bs,\
					char *flag)\
					__attribute__((__nonnull__(1, 2)));

t_ash			ft_ash_init(t_gpa *gpa, t_arena *arena,\
					t_writer *stdout_w, t_writer *stderr_w)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

t_result		ft_ash_apply_conf(t_ash *bs, t_ash_opts opts,\
					t_array2d flags, t_array2d ldflags)\
					__attribute__((__nonnull__(1)));

/*
** The phases of a build, separate calls over one t_ash: they share every
** bit of state through bs, so they are ordered and not independent. Setup
** takes the user's flags and files, names every object and makes the
** directories they imply; compile spawns the toolchain once per file and
** takes no argument of its own, reading back what setup left in bs. The
** link phase stays private (ft__ash_link): ft_ash_runner is what reaches
** it.
**
** ft_ash_runner runs all of them in order, which is the whole build for a
** caller that has one file list. Progress buffers, so stdout is drained
** there and only there, on the way out.
*/

t_result		ft_ash_runner_setup(t_ash *bs, t_array2d_soa files,\
					t_array2d cflags, t_array2d ldflags)\
					__attribute__((__nonnull__(1)));

t_result		ft_ash_compile(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		ft_ash_runner(t_ash *bs, t_array2d_soa files,\
					t_array2d cflags, t_array2d ldflags)\
					__attribute__((__nonnull__(1)));

t_arch			ft_ash_get_compiler_arch(void) __attribute__((const));

t_result		ft_ash_conf_normalize(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_chain(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		ft_ash_conf_runtime(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_cpu(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_target(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_linker(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_stack_check(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_optimizations(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_lto(t_ash *bs)\
					__attribute__((__nonnull__(1)));
t_result		ft_ash_conf_sanitizers(t_ash *bs)\
					__attribute__((__nonnull__(1)));
void			ft_ash_destroy(t_ash *__restrict__ const bs)\
					__attribute__((__nonnull__(1)));

#endif
