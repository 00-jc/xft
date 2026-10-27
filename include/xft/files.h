/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:06:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 18:23:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include <xft/primitives.h>
# include <xft/types/asm_types.h>

# ifdef _WIN64

typedef t_uptr		t_fd;

# else

typedef t_u32a		t_fd;

# endif

typedef enum e_seek : t_u8
{
	SEEK_FROM_0,
	SEEK_FROM_CUR,
	SEEK_FROM_END,
}	t_seek;

typedef struct s_fileopen_mode
{
	t_u8	read		: 1;
	t_u8	write		: 1;
	t_u8	truncate	: 1;
	t_u8	append		: 1;
	t_u8	create		: 1;
	t_u8	exclusive	: 1;
}	t_fileopen_mode;

typedef enum e_file_type : t_u8
{
	F_T_SYML,
	F_T_DISK,
	F_T_SOCK,
	F_T_BLK,
	F_T_DEV,
	F_T_PIPE,
	F_T_DIR,
	F_T_UNKNOWN,
}	t_file_type;

typedef enum e_file_lock : t_u8
{
	LCK_NONE,
	LCK_SHARED,
	LCK_EXCLUSIVE,
}	t_file_lock;

typedef struct s_file_perms
{
	t_u16	o_exec	: 1;
	t_u16	o_write	: 1;
	t_u16	o_read	: 1;
	t_u16	g_exec	: 1;
	t_u16	g_write	: 1;
	t_u16	g_read	: 1;
	t_u16	u_exec	: 1;
	t_u16	u_write	: 1;
	t_u16	u_read	: 1;
	t_u16	sticky	: 1;
	t_u16	setgid	: 1;
	t_u16	setuid	: 1;
	t_u16	_pad	: 4;
}	t_file_perms;

// used for creation / opening
typedef struct s_fs_opts
{
	t_fileopen_mode	mode;
	t_file_lock		lock;
	t_file_perms	perms;
	bool			is_async;
}	t_fs_opts;

typedef struct s_file_info
{
	t_u64a				size;
	t_u64a				blk_size;
	t_u64a				n_blks;
	t_u64a				acc_time;
	t_u64a				mod_time;
	t_u64a				chg_time;
	t_u64a				bth_time;
	t_u64a				inode;
	t_u64a				dev_id;
	t_u32a				lnk_cnt;
	t_file_perms		perms;
	t_file_type			type;
}	t_file_info;

t_fd		xft_open_file(t_blk8r path, t_fileopen_mode mode)\
				__attribute__((__nonnull__(1)));
t_fd		xft_close_file(t_fd fd);
t_file_info	xft_file_info(t_blk8r path);

#endif
