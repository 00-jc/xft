/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 10:28:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_H
# define SYSCALLS_H

# include "primitives.h"
# include "types/timing_types.h"
# include "private/ft_p_syscalls.h"
# include <linux/perf_event.h>
# include "types/io_types.h"

# ifdef FT_REQUIRE_LIBC

#  include <sys/stat.h>
#  include <sys/syscall.h>
#  include <sys/mman.h>
#  include <fcntl.h>
#  include <unistd.h>
#  include <syscall.h>

typedef struct stat		t_stat;
typedef struct flock	t_flock;

# else

typedef t_u64			t_dev;
typedef t_u64			t_ino;
typedef t_u32			t_mode;
typedef t_u64			t_nlink;
typedef t_u32			t_uid;
typedef t_u32			t_gid;
typedef t_i64			t_off;
typedef t_i64			t_blksize;
typedef t_i64			t_blkcnt;

typedef struct s_flock
{
	t_i16	l_type;
	t_i16	l_whence;
	t_i64	l_start;
	t_i64	l_len;
	t_i32	l_pid;
}	t_flock;

typedef struct s_stat
{
	t_dev				st_dev;
	t_ino				st_ino;
	t_mode				st_mode;
	t_nlink				st_nlink;
	t_uid				st_uid;
	t_gid				st_gid;
	t_dev				st_rdev;
	t_off				st_size;
	t_blksize			st_blksize;
	t_blkcnt			st_blocks;
	t_timespec			st_atim;
	t_timespec			st_mtim;
	t_timespec			st_ctim;
}	t_stat;

# endif

void	*ft_mmap(t_size size, long prot_extra, long flags_extra);
void	*ft_fmap(t_size size, int fd);
void	ft_munmap(void *__restrict__ const mem, t_size size)\
			__attribute__((nonnull(1)));
t_u32a	ft_fcntl(t_u32a fd, t_u32a cmd,\
			const t_flock *__restrict__ const arg)\
			__attribute__((nonnull(3)));
t_u32a	ft_lockf(int fd);
t_u32a	ft_unlockf(int fd);
int		ft_ioctl(int fd, t_u64a request, t_u64a arg);
int		ft_open(const char *__restrict__ path, int flags)\
			__attribute__((__nonnull__(1)));
int		ft_close(int fd);
int		ft_stat(const char *__restrict__ path, t_stat *statbuf)\
			__attribute__((__nonnull__(1)));

void	*ft_mremap(t_size size, t_size new_size,\
			void *addr, long flags_extra)\
			__attribute__((__nonnull__(3)));

t_ssize	ft_write(int fd, t_u8 *restrict const buffer, t_size len)\
			__attribute__((__nonnull__(2)));

t_ssize	ft_read(int fd, t_u8 *restrict const buffer, t_size len)\
			__attribute__((__nonnull__(2)));

void	ft_exit(int status)\
			__attribute__((__cold__, __noreturn__));

t_i64a	ft_clock_gettime(t_timespec *__restrict__ const ts)\
			__attribute__((__nonnull__(1)));

int		ft_perf_event_open(const struct perf_event_attr *restrict attr,\
				int group_fd)\
				__attribute__((__nonnull__(1), __always_inline__));

int		ft_getpid(void);

int		ft_sched_setaffinity(int pid, t_size cpusetsize,\
				const t_u64a *restrict const mask)\
				__attribute__((__nonnull__(3), __always_inline__));

t_ssize	ft_writev(int fd, t_iovec *buffers, t_size len)\
			__attribute__((__nonnull__(2), __always_inline__));

#endif
