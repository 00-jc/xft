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

typedef struct stat		t_stat;
typedef struct flock	t_flock;

# else

typedef t_u64			t_dev;
typedef t_u64			t_ino;
typedef t_u32			t_mode;
typedef t_u32			t_uid;
typedef t_u32			t_gid;
typedef t_i64			t_off;
typedef t_i64			t_blkcnt;

typedef struct s_flock
{
	t_i16	l_type;
	t_i16	l_whence;
	t_i64	l_start;
	t_i64	l_len;
	t_i32	l_pid;
}	t_flock;

#  if defined(__x86_64__)

typedef t_u64			t_nlink;
typedef t_i64			t_blksize;

typedef struct s_stat
{
	t_dev				st_dev;
	t_ino				st_ino;
	t_nlink				st_nlink;
	t_mode				st_mode;
	t_uid				st_uid;
	t_gid				st_gid;
	t_i32				_1;
	t_dev				st_rdev;
	t_off				st_size;
	t_blksize			st_blksize;
	t_blkcnt			st_blocks;
	t_timespec			st_atim;
	t_timespec			st_mtim;
	t_timespec			st_ctim;
	t_i64				_2[3];
}	t_stat;

#  elif defined(__aarch64__)

typedef t_u32			t_nlink;
typedef t_i32			t_blksize;

typedef struct s_stat
{
	t_dev				st_dev;
	t_ino				st_ino;
	t_mode				st_mode;
	t_nlink				st_nlink;
	t_uid				st_uid;
	t_gid				st_gid;
	t_dev				st_rdev;
	t_u64				_1;
	t_off				st_size;
	t_blksize			st_blksize;
	t_i32				_2;
	t_blkcnt			st_blocks;
	t_timespec			st_atim;
	t_timespec			st_mtim;
	t_timespec			st_ctim;
	t_i64				_3[3];
}	t_stat;

#  else

#   error "Cannot find arch-specific structs without libc"

#  endif

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
