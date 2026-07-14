/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_HPP
# define SYSCALLS_HPP

# include "c.hpp"
# include "detail.hpp"

namespace xft
{
namespace syscalls
{

namespace c = xft::c;

/* thin, exact-semantics wrappers: every function keeps its C name,
 * parameter order and return value, just namespaced and marked
 * FT_NOEXCEPT (none of these can throw, they report failure through
 * explicit return values - exit() terminates the process instead, same
 * as the C function it wraps; FT_NOEXCEPT is the C++98 spelling of
 * "never unwinds"). t_stat, t_flock, t_iovec and t_timespec are plain,
 * arch-dependent data structs with no lifetime or allocator of their
 * own (built once, handed to a syscall by pointer), so they stay
 * module-owned types under c:: here, exactly like the packed math
 * structs in math.h. */

inline t_any	mmap(t_size size, long prot_extra, long flags_extra) FT_NOEXCEPT
{
	return (c::ft_mmap(size, prot_extra, flags_extra));
}

inline t_any	fmap(t_size size, int fd) FT_NOEXCEPT
{
	return (c::ft_fmap(size, fd));
}

inline void	munmap(t_any __restrict__ const mem, t_size size) FT_NOEXCEPT
{
	c::ft_munmap(mem, size);
}

inline t_u32a	fcntl(t_u32a fd, t_u32a cmd,
		const c::t_flock *__restrict__ const arg) FT_NOEXCEPT
{
	return (c::ft_fcntl(fd, cmd, arg));
}

inline t_u32a	lockf(int fd) FT_NOEXCEPT
{
	return (c::ft_lockf(fd));
}

inline t_u32a	unlockf(int fd) FT_NOEXCEPT
{
	return (c::ft_unlockf(fd));
}

inline int	ioctl(int fd, t_u64a request, t_u64a arg) FT_NOEXCEPT
{
	return (c::ft_ioctl(fd, request, arg));
}

inline int	open(const char *__restrict__ path, int flags) FT_NOEXCEPT
{
	return (c::ft_open(path, flags));
}

inline int	close(int fd) FT_NOEXCEPT
{
	return (c::ft_close(fd));
}

inline int	stat(const char *__restrict__ path,
		c::t_stat *statbuf) FT_NOEXCEPT
{
	return (c::ft_stat(path, statbuf));
}

inline t_any	mremap(t_size size, t_size new_size, t_any addr,
		long flags_extra) FT_NOEXCEPT
{
	return (c::ft_mremap(size, new_size, addr, flags_extra));
}

inline t_ssize	write(int fd, t_u8 *__restrict__ const buffer,
		t_size len) FT_NOEXCEPT
{
	return (c::ft_write(fd, buffer, len));
}

inline t_ssize	read(int fd, t_u8 *__restrict__ const buffer,
		t_size len) FT_NOEXCEPT
{
	return (c::ft_read(fd, buffer, len));
}

inline void	exit(int status) FT_NOEXCEPT
	__attribute__((__noreturn__));

inline void	exit(int status) FT_NOEXCEPT
{
	c::ft_exit(status);
}

inline t_i64a	clock_gettime(c::t_timespec *__restrict__ const ts) FT_NOEXCEPT
{
	return (c::ft_clock_gettime(ts));
}

inline int	perf_event_open(const c::t_perf_event_attr *__restrict__ attr,
		int group_fd) FT_NOEXCEPT
{
	return (c::ft_perf_event_open(attr, group_fd));
}

inline int	getpid(void) FT_NOEXCEPT
{
	return (c::ft_getpid());
}

inline int	sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *__restrict__ const mask) FT_NOEXCEPT
{
	return (c::ft_sched_setaffinity(pid, cpusetsize, mask));
}

inline t_ssize	writev(int fd, c::t_iovec *buffers, t_size len) FT_NOEXCEPT
{
	return (c::ft_writev(fd, buffers, len));
}

inline long	futex_wait(t_u32a *__restrict__ const uaddr) FT_NOEXCEPT
{
	return (c::ft_futex_wait(uaddr));
}

inline long	futex_wake(t_u32a *__restrict__ const uaddr) FT_NOEXCEPT
{
	return (c::ft_futex_wake(uaddr));
}

inline int	mprotect(t_any addr, t_size size, int prot) FT_NOEXCEPT
{
	return (c::ft_mprotect(addr, size, prot));
}

inline int	set_tid_address(t_any address) FT_NOEXCEPT
{
	return (c::ft_set_tid_address(address));
}

inline int	sigprocmask(t_u32a flags, c::t_sigset *__restrict__ const set,
		c::t_sigset *__restrict__ const oldest) FT_NOEXCEPT
{
	return (c::ft_sigprocmask(flags, set, oldest));
}

}
}

#endif
