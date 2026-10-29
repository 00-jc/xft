/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_syscalls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SYSCALLS_H
# define XFT_P_SYSCALLS_H

# include <xft/types/xft_p_syscalls_types.h>

t_any		xft_mmap(t_size size, t_u64a prot, t_u64a flags);
t_result	xft_mmap_commit(t_any ptr, t_size size,\
				t_u64a prot, t_u64a flags_extra)\
				__attribute__((__nonnull__(1)));
t_any		xft_fmap(t_size size, t_u64a prot, t_u64a flags, int fd);
t_result	xft_map_failed(t_cany ptr)\
			__attribute__((const));
void		xft_munmap(t_any __restrict__ const mem, t_size size)\
			__attribute__((__nonnull__(1)));
t_i32a		xft_fcntl(t_u32a fd, t_u32a cmd,\
			const t_flock *__restrict__ const arg)\
			__attribute__((__nonnull__(3)));
t_i32a		xft_lockf(int fd);
t_i32a		xft_unlockf(int fd);
int			xft_open(const char *__restrict__ path, int flags, t_u32a mode)\
			__attribute__((__nonnull__(1)));
int			xft_close(int fd);
int			xft_statx(const char *__restrict__ path, t_u32a flags,\
			t_u32a mask, t_statx *statxbuf)\
			__attribute__((__nonnull__(1, 4)));
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

void		xft_exit_group(t_i32a status)\
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

int			xft_prlimit64(t_i32a pid, t_xft_rlimit resource,\
				const t_rlimit *new_limit, t_rlimit *__restrict__ old_limit)\
				__attribute__((__nonnull__(4)));

t_ssize		xft_writev(int fd, t_iovec *buffers, t_size len)\
			__attribute__((__nonnull__(2)));

t_i64a		xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)\
			__attribute__((__nonnull__(1)));

t_i64a		xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)\
			__attribute__((__nonnull__(1)));

int			xft_mprotect(t_any addr, t_size size, int prot)\
			__attribute__((__nonnull__(1)));

int			xft_madvise(t_any addr, t_size size, int advice)\
			__attribute__((__nonnull__(1)));

int			xft_set_tid_address(t_any address);

t_i32		xft_clone(const t_clone_arg *__restrict__ const args)\
			__attribute__((__nonnull__(1)));

t_i32		xft_fork(void);

t_i32		xft_wait4(t_i32 pid, t_i32a *status, t_i32 options,\
			t_any rusage);

int			xft_ioctl(int fd, t_u64a request, t_u64a arg);

int			xft_perf_event_open(const t_perf_event_attr *restrict attr,\
				int group_fd)\
				__attribute__((__nonnull__(1)));

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

t_i64a		xft_syscall6(t_u64a nr, const t_u64a args[6])\
			__attribute__((__nonnull__(2)));

# endif

#endif
