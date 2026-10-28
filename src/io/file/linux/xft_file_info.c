/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:42:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 22:42:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/files.h>

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

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_file_info	xft_file_info(t_blk8r path)
{
	t_statx		st;
	t_file_info	info;

	if (__builtin_expect(xft_statx((const char *)path,
				xft_at_symlink_nofollow,
				xft_statx_basic_stats | xft_statx_btime, &st), 0))
		return ((t_file_info){.type = F_T_UNKNOWN});
	info = (t_file_info){
		.size = st.stx_size,
		.blk_size = st.stx_blksize,
		.n_blks = st.stx_blocks,
		.acc_time = xft__nanos(st.stx_atime.tv_sec, st.stx_atime.tv_nsec),
		.mod_time = xft__nanos(st.stx_mtime.tv_sec, st.stx_mtime.tv_nsec),
		.chg_time = xft__nanos(st.stx_ctime.tv_sec, st.stx_ctime.tv_nsec),
		.bth_time = xft__nanos(st.stx_btime.tv_sec, st.stx_btime.tv_nsec),
		.inode = st.stx_ino,
		.dev_id = (t_u64a)st.stx_dev_major << 32 | st.stx_dev_minor,
		.lnk_cnt = st.stx_nlink,
		.type = xft__file_type(st.stx_mode),
	};
	*(t_u16a *)&info.perms = st.stx_mode & xft_mode_perms;
	return (info);
}

#endif
