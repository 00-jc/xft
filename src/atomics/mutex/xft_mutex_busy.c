/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_busy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 20:23:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "types/atomic_types.h"
#include "xft_p_atomics.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_mutex_busy(t_mutex *__restrict__ const mutex)
{
	t_u64				iters;
	t_i32				val;
	static t_i32 const	contest = XFT_CONTESTED;

	((xft_prefetch0((t_any)mutex, sizeof(*mutex))), val = XFT_UNLOCKED);
	iters = 0;
	while (true)
	{
		__atomic_load(mutex, &val, __ATOMIC_RELAXED);
		if (__builtin_expect(val == XFT_UNLOCKED, 1))
		{
			if (__builtin_expect(__atomic_compare_exchange(mutex,
						&val, (t_i32 *) & contest, true,
						__ATOMIC_ACQUIRE, __ATOMIC_RELAXED), 1))
				return ;
		}
		xft_mutex_backoff(xft_last_pow2(iters++ | 1));
		iters &= (1ULL << 11) - 1;
	}
}
