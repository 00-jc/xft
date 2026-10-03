/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_slow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 17:41:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"
#include "syscalls.h"
#include "types/atomic_types.h"
#include "xft_p_atomics.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_mutex_slow(t_mutex *__restrict__ const mutex)
{
	t_i32				val;
	static t_i32 const	contest = XFT_CONTESTED;

	val = XFT_UNLOCKED;
	while (true)
	{
		__atomic_exchange(mutex, (t_i32 *) & contest, &val, __ATOMIC_ACQ_REL);
		if (__builtin_expect(val == XFT_UNLOCKED, 1))
			return ;
		xft_futex_wait((t_any)mutex, XFT_CONTESTED);
	}
}
