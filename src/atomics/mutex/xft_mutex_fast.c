/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_fast.c                                   :+:      :+:    :+:   */
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
#include "xft_p_atomics.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline bool	xft__try_lock(t_mutex *__restrict__ const mutex)
{
	t_i32				val;
	static t_i32 const	contest = XFT_CONTESTED;

	__atomic_exchange(mutex, (t_i32 *) & contest, &val, __ATOMIC_ACQ_REL);
	if (__builtin_expect(val == XFT_UNLOCKED, 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline bool	xft__try_lock_spin(t_mutex *__restrict__ const mutex)
{
	t_i32				val;
	static t_i32 const	contest = XFT_CONTESTED;

	val = XFT_UNLOCKED;
	if (__builtin_expect(__atomic_compare_exchange(mutex,
				&val, (t_i32 *) & contest, true, __ATOMIC_ACQUIRE,
				__ATOMIC_RELAXED), 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_mutex_spin(t_mutex *__restrict__ const mutex)
{
	t_u64				iters;
	t_i32				val;

	((xft_prefetch0((t_any)mutex, sizeof(*mutex))), val = XFT_UNLOCKED);
	while (true)
	{
		iters = 0;
		while (iters < XFT_MUTEX_SPIN)
		{
			__atomic_load(mutex, &val, __ATOMIC_RELAXED);
			if (__builtin_expect(val == XFT_UNLOCKED, 1))
			{
				if (__builtin_expect(xft__try_lock_spin(mutex), 1))
					return ;
			}
			xft_mutex_backoff(xft_last_pow2(iters++ | 1));
		}
		if (__builtin_expect(xft__try_lock(mutex), 0))
			return ;
		xft_futex_wait((t_any)mutex, XFT_CONTESTED);
		if (__builtin_expect(xft__try_lock(mutex), 1))
			return ;
	}
}
