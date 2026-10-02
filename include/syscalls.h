/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 13:48:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_H
# define SYSCALLS_H

# define XFT_MAX_ERRNO 4095

# include "primitives.h"
# include "types/timing_types.h"
# include "types/signal_types.h"
# include "types/io_types.h"

# if defined(XFT_REQUIRE_LIBC) && !defined(_WIN64)

#  include <sys/stat.h>
#  include <sys/mman.h>
#  include <fcntl.h>
#  include <unistd.h>

typedef struct stat		t_stat;
typedef struct flock	t_flock;

# else

#  ifndef PROT_NONE
#   define PROT_NONE                  0x0
#  endif
#  ifndef PROT_READ
#   define PROT_READ                  0x1
#  endif
#  ifndef PROT_WRITE
#   define PROT_WRITE                 0x2
#  endif
#  ifndef PROT_EXEC
#   define PROT_EXEC                  0x4
#  endif
#  ifndef MAP_PRIVATE
#   define MAP_PRIVATE                0x02
#  endif
#  ifndef MAP_ANONYMOUS
#   define MAP_ANONYMOUS              0x20
#  endif
#  ifndef MAP_FAILED
#   define MAP_FAILED                 -1
#  endif
#  ifndef MREMAP_MAYMOVE
#   define MREMAP_MAYMOVE             1
#  endif
#  ifndef F_RDLCK
#   define F_RDLCK                    0
#  endif
#  ifndef F_WRLCK
#   define F_WRLCK                    1
#  endif
#  ifndef F_UNLCK
#   define F_UNLCK                    2
#  endif
#  ifndef F_SETLK
#   define F_SETLK                    6
#  endif
#  ifndef F_SETLKW
#   define F_SETLKW                   7
#  endif
#  ifndef SEEK_SET
#   define SEEK_SET                   0
#  endif
#  ifndef O_RDONLY
#   define O_RDONLY                   0
#  endif
#  ifndef O_WRONLY
#   define O_WRONLY                   1
#  endif
#  ifndef O_RDWR
#   define O_RDWR                     2
#  endif
#  ifndef O_ACCMODE
#   define O_ACCMODE                  3
#  endif
#  ifndef O_CREAT
#   define O_CREAT                    0100
#  endif
#  ifndef O_EXCL
#   define O_EXCL                     0200
#  endif
#  ifndef O_TRUNC
#   define O_TRUNC                    01000
#  endif
#  ifndef O_APPEND
#   define O_APPEND                   02000
#  endif
#  ifndef STDIN_FILENO
#   define STDIN_FILENO               0
#  endif
#  ifndef STDOUT_FILENO
#   define STDOUT_FILENO              1
#  endif
#  ifndef STDERR_FILENO
#   define STDERR_FILENO              2
#  endif

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

# define XFT_WNOHANG				1
# define XFT_WUNTRACED			2

# define XFT_MKDIR_0755			0755

t_any		xft_mmap(t_size size, t_u64a prot, t_u64a flags_extra);
t_any		xft_fmap(t_size size, int fd);
t_result	xft_map_failed(t_cany ptr)\
			__attribute__((const));
void		xft_munmap(t_any __restrict__ const mem, t_size size)\
			__attribute__((__nonnull__(1)));
t_i32a		xft_fcntl(t_u32a fd, t_u32a cmd,\
			const t_flock *__restrict__ const arg)\
			__attribute__((__nonnull__(3)));
t_i32a		xft_lockf(int fd);
t_i32a		xft_unlockf(int fd);
int			xft_open(const char *__restrict__ path, int flags)\
			__attribute__((__nonnull__(1)));
int			xft_close(int fd);
int			xft_stat(const char *__restrict__ path, t_stat *statbuf)\
			__attribute__((__nonnull__(1, 2)));
int			xft_mkdir(const char *__restrict__ path, t_u32a mode)\
			__attribute__((__nonnull__(1)));

t_any		xft_mremap(t_size size, t_size new_size,\
			t_any addr, t_u64a flags_extra)\
			__attribute__((__nonnull__(3)));

t_ssize		xft_write(int fd, t_u8 *restrict const buffer, t_size len)\
			__attribute__((__nonnull__(2)));

t_ssize		xft_read(int fd, t_u8 *restrict const buffer, t_size len)\
			__attribute__((__nonnull__(2)));

void		xft_exit(int status)\
			__attribute__((__cold__, __noreturn__));

t_i64a		xft_clock_gettime(t_timespec *__restrict__ const ts)\
			__attribute__((__nonnull__(1)));

int			xft_getpid(void);

int			xft_sched_setaffinity(int pid, t_size cpusetsize,\
				const t_u64a *restrict const mask)\
				__attribute__((__nonnull__(3)));

int			xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,\
				const t_u64a *__restrict__ mask)\
				__attribute__((__nonnull__(3)));

t_result	xft_get_cpu_count(t_size *count)\
				__attribute__((__nonnull__(1)));

t_ssize		xft_writev(int fd, t_iovec *buffers, t_size len)\
			__attribute__((__nonnull__(2)));

t_i64a		xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)\
			__attribute__((__nonnull__(1)));

t_i64a		xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)\
			__attribute__((__nonnull__(1)));

int			xft_mprotect(t_any addr, t_size size, int prot)\
			__attribute__((__nonnull__(1)));

int			xft_set_tid_address(t_any address);

int			xft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,\
			t_sigset *__restrict__ const oldest);

t_i32		xft_clone(const t_clone_arg *__restrict__ const args)\
			__attribute__((__nonnull__(1)));

t_i32		xft_fork(void);

t_i32		xft_wait4(t_i32 pid, t_i32a *status, t_i32 options,\
			t_any rusage);

#endif
