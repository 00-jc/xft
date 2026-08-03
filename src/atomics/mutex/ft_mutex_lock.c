/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_lock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:26:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 17:37:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"
#include "types/atomic_types.h"
#include "private/ft_p_atomics.h"

__attribute__((__nonnull__(1)))
inline void	ft_mutex_lock(t_mutex *__restrict__ const mutex,
	const t_mutex_type type)
{
	bool				ret;
	t_i32				val;
	static t_i32 const	lock = FT_LOCKED;

	val = FT_UNLOCKED;
	ret = __atomic_compare_exchange(mutex, &val, (t_i32 *) & lock,
			false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
	if (__builtin_expect(ret, 1))
		return ;
	if (type == FAST)
		ft_mutex_spin(mutex);
	else if (type == BUSY)
		ft_mutex_busy(mutex);
	else if (type == SLOW)
		ft_mutex_slow(mutex);
	else
		__builtin_unreachable();
}
