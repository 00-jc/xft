/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_lock.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:26:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 17:37:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <xft/types/atomic_types.h>
#include <xft/xft_p_atomics.h>

__attribute__((__nonnull__(1), __used__))
inline void	xft_mutex_lock(t_mutex *__restrict__ const mutex,
	const t_mutex_type type)
{
	bool				ret;
	t_i32				val;
	static t_i32 const	lock = XFT_LOCKED;

	val = XFT_UNLOCKED;
	ret = __atomic_compare_exchange(mutex, &val, (t_i32 *) & lock,
			false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
	if (__builtin_expect(ret, 1))
		return ;
	if (type == xft_lock_fast)
		xft_mutex_spin(mutex);
	else if (type == xft_lock_busy)
		xft_mutex_busy(mutex);
	else if (type == xft_lock_slow)
		xft_mutex_slow(mutex);
	else
		__builtin_unreachable();
}
