/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_busy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 22:34:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "types/atomic_types.h"
#include "private/ft_p_atomics.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_mutex_busy(t_mutex *__restrict__ const mutex)
{
	t_u64				iters;
	t_i32				val;
	static t_i32 const	contest = FT_CONTESTED;

	((void)(ft_prefetch0((t_any)mutex, sizeof(*mutex))), val = FT_UNLOCKED);
	iters = 0;
	while (true)
	{
		__atomic_load(mutex, &val, __ATOMIC_RELAXED);
		if (__builtin_expect(val == FT_UNLOCKED, 1))
		{
			if (__builtin_expect(__atomic_compare_exchange(mutex,
						(t_any) & val, (t_any) & contest, true,
						__ATOMIC_ACQUIRE, __ATOMIC_RELAXED), 1))
				return ;
		}
		ft_mutex_backoff(ft_last_pow2(iters++ | 1));
		iters &= (1ULL << 11) - 1;
	}
}
