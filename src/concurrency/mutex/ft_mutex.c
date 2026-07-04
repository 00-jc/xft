/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 22:27:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:31:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"
#include "mem.h"
#include "syscalls.h"

__attribute__((__always_inline__))
inline void	ft_mutex_backoff(t_u64 n)
{
	while (n--)
		__builtin_ia32_pause();
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_mutex_spin(t_mutex *__restrict__ const mutex)
{
	t_u64				iters;
	t_i32				val;
	static t_i32 const	contest = FT_CONTESTED;

	((void)(ft_prefetch0((t_any)mutex, sizeof(*mutex))), val = FT_UNLOCKED);
	while (true)
	{
		iters = FT_MUTEX_SPIN;
		while (iters-- > FT_UNLOCKED)
		{
			__atomic_load(mutex, &val, __ATOMIC_RELAXED);
			if (__builtin_expect(val == FT_UNLOCKED, 1))
			{
				if (__builtin_expect(__atomic_compare_exchange(mutex,
							(t_any) & val, (t_any) & contest, true,
							__ATOMIC_ACQUIRE, __ATOMIC_RELAXED), 1))
					return ;
			}
			ft_mutex_backoff(ft_last_pow2(iters));
		}
		__atomic_exchange(mutex, (t_any) & contest, &val, __ATOMIC_ACQ_REL);
		if (__builtin_expect(val == FT_UNLOCKED, 0))
			return ;
		ft_futex_wait((t_any)mutex);
	}
}

__attribute__((__nonnull__(1)))
inline void	ft_mutex_lock(t_mutex *__restrict__ const mutex)
{
	bool				ret;
	t_i32				val;
	static t_i32 const	lock = FT_LOCKED;

	val = FT_UNLOCKED;
	ret = __atomic_compare_exchange(mutex, &val, (t_any) & lock,
			false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
	if (__builtin_expect(ret, 1))
		return ;
	ft_mutex_spin(mutex);
}

__attribute__((__nonnull__(1)))
inline void	ft_mutex_unlock(t_mutex *__restrict__ const mutex)
{
	t_i32				val;

	ft_prefetch0((t_any)mutex, sizeof(*mutex));
	val = __atomic_fetch_sub(mutex, 1, __ATOMIC_RELEASE);
	if (__builtin_expect(val == FT_CONTESTED, 1))
	{
		__atomic_clear(mutex, __ATOMIC_RELEASE);
		ft_futex_wake((t_any)mutex);
	}
}
