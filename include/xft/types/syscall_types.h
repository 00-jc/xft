/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALL_TYPES_H
# define SYSCALL_TYPES_H

# include <xft/primitives.h>
# include <xft/types/timing_types.h>
# include <xft/types/signal_types.h>
# include <xft/types/io_types.h>

# if defined(XFT_REQUIRE_LIBC) && !defined(_WIN32)

#  include <sys/stat.h>
#  include <sys/mman.h>
#  include <fcntl.h>
#  include <unistd.h>

typedef struct statx	t_statx;
typedef struct flock	t_flock;

# elif defined(__linux__)

typedef struct s_flock
{
	t_i16	l_type;
	t_i16	l_whence;
	t_i64	l_start;
	t_i64	l_len;
	t_i32	l_pid;
}	t_flock;

typedef struct s_statx_ts
{
	t_i64				tv_sec;
	t_u32				tv_nsec;
	t_i32				_1;
}	t_statx_ts;

typedef struct s_statx
{
	t_u32				stx_mask;
	t_u32				stx_blksize;
	t_u64				stx_attributes;
	t_u32				stx_nlink;
	t_u32				stx_uid;
	t_u32				stx_gid;
	t_u16				stx_mode;
	t_u16				_1;
	t_u64				stx_ino;
	t_u64				stx_size;
	t_u64				stx_blocks;
	t_u64				stx_attributes_mask;
	t_statx_ts			stx_atime;
	t_statx_ts			stx_btime;
	t_statx_ts			stx_ctime;
	t_statx_ts			stx_mtime;
	t_u32				stx_rdev_major;
	t_u32				stx_rdev_minor;
	t_u32				stx_dev_major;
	t_u32				stx_dev_minor;
	t_u64				_2[14];
}	t_statx;

# endif

typedef struct s_clone_arg
{
	t_u64	flags;
	t_any	stack;
	t_i32a	*ptid;
	t_i32a	*ctid;
	t_uptr	tls;
}	t_clone_arg;

#endif
