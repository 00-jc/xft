/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__always_inline__, __const__))
static inline t_u64a	xft__nanos(t_i64 sec, t_u32 nsec)
{
	return ((t_u64a)sec * 1000000000 + nsec);
}

// indexed by the S_IFMT nibble of st_mode
__attribute__((__always_inline__, __const__))
static inline t_file_type	xft__file_type(t_u16 mode)
{
	static const t_file_type	types[16] = {
		F_T_UNKNOWN, F_T_PIPE, F_T_DEV, F_T_UNKNOWN,
		F_T_DIR, F_T_UNKNOWN, F_T_BLK, F_T_UNKNOWN,
		F_T_DISK, F_T_UNKNOWN, F_T_SYML, F_T_UNKNOWN,
		F_T_SOCK, F_T_UNKNOWN, F_T_UNKNOWN, F_T_UNKNOWN,
	};

	return (types[mode >> 12]);
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	xft__from_statx(const t_statx *st, t_file_info *info)
{
	*info = (t_file_info){
		.size = st->stx_size,
		.blk_size = st->stx_blksize,
		.n_blks = st->stx_blocks,
		.acc_time = xft__nanos(st->stx_atime.tv_sec, st->stx_atime.tv_nsec),
		.mod_time = xft__nanos(st->stx_mtime.tv_sec, st->stx_mtime.tv_nsec),
		.chg_time = xft__nanos(st->stx_ctime.tv_sec, st->stx_ctime.tv_nsec),
		.bth_time = xft__nanos(st->stx_btime.tv_sec, st->stx_btime.tv_nsec),
		.inode = st->stx_ino,
		.dev_id = (t_u64a)st->stx_dev_major << 32 | st->stx_dev_minor,
		.lnk_cnt = st->stx_nlink,
		.type = xft__file_type(st->stx_mode),
	};
	*(t_u16a *)&info->perms = st->stx_mode & xft_mode_perms;
}

__attribute__((__nonnull__(1, 2)))
t_result	xft_fileinfo_from_name(const char *name, t_file_info *fileinfo)
{
	const t_u32a	mask = xft_statx_basic_stats | xft_statx_btime;
	t_statx			st;
	t_result		ret;

	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_statx(name, xft_at_symlink_nofollow, mask, &st);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft__from_statx(&st, fileinfo);
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2)))
t_result	xft_fileinfo_from_fd(t_fd fd, t_file_info *fileinfo)
{
	const t_u32a	mask = xft_statx_basic_stats | xft_statx_btime;
	t_statx			st;
	t_result		ret;

	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_fstatx((int)fd, mask, &st);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft__from_statx(&st, fileinfo);
	return ((t_result){.ok = OK});
}

#endif
