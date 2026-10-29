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

#include <xft/atomics.h>
#include <xft/mem.h>
#include <xft/types/atomic_types.h>
#include <xft/xft_p_atomics.h>
#include <stdatomic.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
static inline bool	xft__try_lock(t_mutex *__restrict__ const mutex)
{
	if (__builtin_expect(atomic_exchange_explicit(mutex, xft_contested,
				xft_acq_rel) == xft_unlocked, 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
static inline bool	xft__try_lock_spin(t_mutex *__restrict__ const mutex)
{
	t_i32	val;

	val = xft_unlocked;
	if (__builtin_expect(atomic_compare_exchange_weak_explicit(mutex,
				&val, xft_contested, xft_acquire,
				xft_relaxed), 1))
		return (true);
	return (false);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_mutex_spin(t_mutex *__restrict__ const mutex)
{
	t_size				iters;
	t_i32				val;

	((xft_prefetch_write0((t_any)mutex, sizeof(*mutex))), val = xft_unlocked);
	while (true)
	{
		iters = 0;
		while (iters < XFT_MUTEX_SPIN)
		{
			val = atomic_load_explicit(mutex, xft_relaxed);
			if (__builtin_expect(val == xft_unlocked, 1))
			{
				if (__builtin_expect(xft__try_lock_spin(mutex), 1))
					return ;
			}
			xft_mutex_backoff(xft_last_pow2(iters++ | 1));
		}
		if (__builtin_expect(xft__try_lock(mutex), 0))
			return ;
		WaitOnAddress(mutex, &(t_i32){xft_contested}, sizeof(*mutex), INFINITE);
		if (__builtin_expect(xft__try_lock(mutex), 1))
			return ;
	}
}

#endif
