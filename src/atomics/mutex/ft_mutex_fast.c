/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_fast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 20:22:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"
#include "mem.h"
#include "syscalls.h"
#include "types/atomic_types.h"
#include "private/ft_p_atomics.h"

__attribute__((__nonnull__(1), __always_inline__))
inline bool	ft__try_lock(t_mutex *__restrict__ const mutex)
{
	t_i32				val;
	static t_i32 const	contest = FT_CONTESTED;

	__atomic_exchange(mutex, (t_i32 *) & contest, &val, __ATOMIC_ACQ_REL);
	if (__builtin_expect(val == FT_UNLOCKED, 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__))
inline bool	ft__try_lock_spin(t_mutex *__restrict__ const mutex)
{
	t_i32				val;
	static t_i32 const	contest = FT_CONTESTED;

	val = FT_UNLOCKED;
	if (__builtin_expect(__atomic_compare_exchange(mutex,
				&val, (t_i32 *) & contest, true, __ATOMIC_ACQUIRE,
				__ATOMIC_RELAXED), 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_mutex_spin(t_mutex *__restrict__ const mutex)
{
	t_u64				iters;
	t_i32				val;

	((ft_prefetch0((t_any)mutex, sizeof(*mutex))), val = FT_UNLOCKED);
	while (true)
	{
		iters = 0;
		while (iters < FT_MUTEX_SPIN)
		{
			__atomic_load(mutex, &val, __ATOMIC_RELAXED);
			if (__builtin_expect(val == FT_UNLOCKED, 1))
			{
				if (__builtin_expect(ft__try_lock_spin(mutex), 1))
					return ;
			}
			ft_mutex_backoff(ft_last_pow2(iters++ | 1));
		}
		if (__builtin_expect(ft__try_lock(mutex), 0))
			return ;
		ft_futex_wait((t_any)mutex, FT_CONTESTED);
		if (__builtin_expect(ft__try_lock(mutex), 1))
			return ;
	}
}
