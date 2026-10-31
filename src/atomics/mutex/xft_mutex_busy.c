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

#include <xft/mem.h>
#include <xft/atomics.h>
#include <xft/types/atomic_types.h>
#include <xft/xft_p_atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1), __always_inline__, __used__, __flatten__))
inline void	xft_mutex_busy(t_mutex *__restrict__ const mutex)
{
	t_size	iters;
	t_u32	val;

	((xft_prefetch_write0((t_any)mutex, sizeof(*mutex))), val = xft_unlocked);
	iters = 0;
	while (true)
	{
		val = atomic_load_explicit(mutex, xft_relaxed);
		if (__builtin_expect(val == xft_unlocked, 1))
		{
			if (__builtin_expect(atomic_compare_exchange_weak_explicit(mutex,
						&val, xft_contested, xft_acquire,
						xft_relaxed), 1))
				return ;
		}
		xft_backoff(xft_last_pow2(iters++ | 1));
		iters &= (1ULL << 11) - 1;
	}
}
