/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_unlock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:52:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 17:04:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "syscalls.h"
#include "atomics.h"

__attribute__((__nonnull__(1), __used__))
inline void	xft_mutex_unlock(t_mutex *__restrict__ const mutex)
{
	t_i32				val;

	xft_prefetch0((t_any)mutex, sizeof(*mutex));
	val = __atomic_fetch_sub(mutex, 1, __ATOMIC_RELEASE);
	if (__builtin_expect(val == XFT_CONTESTED, 1))
	{
		__atomic_store_n(mutex, XFT_UNLOCKED, __ATOMIC_RELEASE);
		xft_futex_wake((t_any)mutex, XFT_LOCKED);
	}
}
