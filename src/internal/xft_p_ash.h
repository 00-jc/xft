/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_ash.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ASH_H
# define XFT_P_ASH_H

# include "ash.h"

# if defined(__x86_64__)
#  define XFT_COMPILER_ARCH X86_64
# elif defined(__aarch64__)
#  define XFT_COMPILER_ARCH AARCH64
# else
#  define XFT_COMPILER_ARCH OTHER
# endif

void			xft__ash_slice(t_u64 *values, const char *str)\
					__attribute__((__nonnull__(1, 2)));

void			xft__ash_log(t_ash *bs, const char *msg)\
					__attribute__((__nonnull__(1, 2)));

t_result		xft__ash_ko(t_ash *bs, const char *msg)\
					__attribute__((__nonnull__(1, 2)));

t_result		xft__ash_ko_flag(t_ash *bs, const char *msg,\
					const char *flag)\
					__attribute__((__nonnull__(1, 2, 3)));

void			xft__ash_print_invocation(t_ash *bs, const char *toolchain)\
					__attribute__((__nonnull__(1, 2)));

void			xft__ash_log_step(t_ash *bs, const char *tool,\
					const char *target)\
					__attribute__((__nonnull__(1, 2, 3)));

void			xft__ash_log_files(t_ash *bs, const char *tool)\
					__attribute__((__nonnull__(1, 2)));

const char		*xft__ash_lto_flag(const t_ash *bs)\
					__attribute__((__nonnull__(1), pure));

t_result		xft__ash_populate_obj_soa(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		xft__ash_mkdir_p(t_ash *bs)\
					__attribute__((__nonnull__(1)));

const char		*xft__ash_get_gcc(void);
const char		*xft__ash_get_clang(void);
const char		*xft__ash_get_zig(void);
const char		*xft__ash_get_toolchain_hardcoded(t_compiler compiler);

t_result		xft__ash_get_toolchain(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

const char		*xft__ash_get_llvm_ar(void);
const char		*xft__ash_get_gcc_ar(void);
const char		*xft__ash_get_archiver_hardcoded(t_compiler compiler);

t_result		xft__ash_get_archiver(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

const char		*xft__ash_get_bfd(void);
const char		*xft__ash_get_lld(void);
const char		*xft__ash_get_mold(void);
const char		*xft__ash_get_linker_hardcoded(t_linker linker);

t_result		xft__ash_get_linker(t_ash *bs, const char **path)\
					__attribute__((__nonnull__(1, 2)));

t_result		xft__ash_rip_it_clang(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		xft__ash_rip_it_gcc(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		xft__ash_link_opt(t_ash *bs)\
					__attribute__((__nonnull__(1)));

t_result		xft__ash_build_argv(t_ash *bs, const char *toolchain,
					char ***argv, char ***file_slot)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

t_result		xft__ash_run_build(t_ash *bs, const char *toolchain,
					char **argv, char **file_slot)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

t_result		xft__ash_spawn(t_ash *bs, const char *path,\
					char **argv, const char *label)\
					__attribute__((__nonnull__(1, 2, 3, 4)));

t_result		xft__ash_build_ar_argv(t_ash *bs, const char *archiver,\
					char ***argv)\
					__attribute__((__nonnull__(1, 2, 3)));

t_result		xft__ash_build_link_argv(t_ash *bs, const char *driver,\
					char ***argv)\
					__attribute__((__nonnull__(1, 2, 3)));

t_result		xft__ash_link(t_ash *bs)\
					__attribute__((__nonnull__(1)));

#endif
