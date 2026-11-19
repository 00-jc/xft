/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_syscalls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 02:00:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SYSCALLS_H
# define XFT_P_SYSCALLS_H

# include <xft/types/xft_p_syscalls_types.h>

t_any			xft_mmap(t_size size, t_u64a prot, t_u64a flags);
t_result		xft_mmap_commit(t_any ptr, t_size size,\
					t_u64a prot, t_u64a flags_extra)\
					__attribute__((__nonnull__(1)));
t_any			xft_fmap(t_size size, t_u64a prot, t_u64a flags, int fd);
t_result		xft_map_failed(t_cany ptr)\
					__attribute__((const));
bool			xft_should_retry(t_result res)\
					__attribute__((const));
void			xft_munmap(t_any __restrict__ const mem, t_size size)\
					__attribute__((__nonnull__(1)));
t_result		xft_fcntl(t_u32a fd, t_u32a cmd,\
					const t_flock *__restrict__ const arg)\
					__attribute__((__nonnull__(3)));
t_result		xft_lockf(int fd);
t_result		xft_unlockf(int fd);
t_result		xft_open(const char *__restrict__ path, int flags, t_u32a mode,\
					int *__restrict__ const fd)\
					__attribute__((__nonnull__(1, 4)));
t_result		xft_close(int fd);
t_result		xft_statx(const char *__restrict__ path, t_u32a flags,\
					t_u32a mask, t_statx *statxbuf)\
					__attribute__((__nonnull__(1, 4)));
t_result		xft_fstatx(int fd, t_u32a mask, t_statx *statxbuf)\
					__attribute__((__nonnull__(3)));
t_result		xft_mkdir(const char *__restrict__ path, t_u32a mode)\
					__attribute__((__nonnull__(1)));

t_any			xft_mremap(t_size size, t_size new_size,\
					t_any addr, t_u64a flags_extra)\
					__attribute__((__nonnull__(3)));

t_result		xft_write(int fd, t_u8 *restrict const buffer, t_size len,\
					t_size *restrict const written)\
					__attribute__((__nonnull__(2, 4)));

t_result		xft_read(int fd, t_u8 *restrict const buffer, t_size len,\
					t_size *restrict const got)\
					__attribute__((__nonnull__(2, 4)));

void			xft_exit(int status)\
					__attribute__((__cold__, __noreturn__));

void			xft_exit_group(t_i32a status)\
					__attribute__((__cold__, __noreturn__));

t_result		xft_clock_gettime(t_timespec *__restrict__ const ts)\
					__attribute__((__nonnull__(1)));

int				xft_getpid(void);

t_result		xft_sched_setaffinity(int pid, t_size cpusetsize,\
					const t_u64a *restrict const mask)\
					__attribute__((__nonnull__(3)));

t_result		xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,\
					const t_u64a *__restrict__ mask,\
					t_size *__restrict__ const written)\
					__attribute__((__nonnull__(3, 4)));

t_result		xft_prlimit64(t_i32a pid, t_xft_rlimit resource,\
					const t_rlimit *new_limit, t_rlimit *__restrict__ old_limit)\
					__attribute__((__nonnull__(4)));

t_result		xft_writev(int fd, t_iovec *buffers, t_size len,\
					t_size *restrict const written)\
					__attribute__((__nonnull__(2, 4)));

t_result		xft_mprotect(t_any addr, t_size size, int prot)\
					__attribute__((__nonnull__(1)));

t_result		xft_madvise(t_any addr, t_size size, int advice)\
					__attribute__((__nonnull__(1)));

int				xft_set_tid_address(t_any address);

t_i32			xft_clone(const t_clone_arg *__restrict__ const args)\
					__attribute__((__nonnull__(1)));

t_result		xft_fork(t_i32 *restrict const pid)\
					__attribute__((__nonnull__(1)));

t_i32			xft_wait4(t_i32 pid, t_i32a *status, t_i32 options,\
					t_any rusage);

t_result		xft_ioctl(int fd, t_u64a request, t_u64a arg);

t_result		xft_perf_event_open(const t_perf_event_attr *restrict attr,\
					int group_fd, int *restrict const fd)\
					__attribute__((__nonnull__(1, 3)));

t_result		xft_socket(int domain, int type, int protocol,\
					int *restrict const fd)\
					__attribute__((__nonnull__(4)));

t_result		xft_bind(int fd, const t_sockaddr *addr, t_u32a addrlen)\
					__attribute__((__nonnull__(2)));

t_result		xft_listen(int fd, int backlog);

t_result		xft_connect(int fd, const t_sockaddr *addr, t_u32a addrlen)\
					__attribute__((__nonnull__(2)));

t_result		xft_setsockopt(int fd, int level, int name, t_iovec value);

t_result		xft_sendto(int fd, t_iovec *restrict buf, t_xft_msg_opts opts,\
					const t_sockaddr_in6 *restrict dest)\
					__attribute__((__nonnull__(2)));

t_result		xft_accept(int fd, int flags, t_sockaddr_in6 *restrict addr,\
					int *restrict const conn)\
					__attribute__((__nonnull__(4)));

t_result		xft_recvfrom(int fd, t_iovec *restrict buf, t_xft_msg_opts opts,\
					t_sockaddr_in6 *restrict from)\
					__attribute__((__nonnull__(2)));

t_result		xft_sendfile(int out_fd, int in_fd, t_i64a *restrict offset,\
					t_size *restrict const count)\
					__attribute__((__nonnull__(4)));

t_result		xft_epoll_create(int flags, int *restrict const epfd)\
					__attribute__((__nonnull__(2)));

t_result		xft_epoll_ctl(int epfd, int op, int fd, t_epoll_event *event);

t_result		xft_epoll_wait(int epfd, t_epoll_event *restrict events,\
					int timeout, int *restrict const ready)\
					__attribute__((__nonnull__(2, 4)));

t_result		xft_epoll_close(int epfd);

# ifndef XFT_REQUIRE_LIBC

t_result		xft_set_thread_pointer(t_uptr tp);

# endif

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

t_i64a			xft_syscall6(t_u64a nr, const t_u64a args[6])\
					__attribute__((__nonnull__(2)));

# endif

#endif
