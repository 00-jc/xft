/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_unlock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:52:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 04:13:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/mem.h>
#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1), __used__, __flatten__))
inline void	xft_mutex_unlock(t_mutex *__restrict__ const mutex)
{
	t_u32				val;

	val = atomic_exchange_explicit(mutex, xft_unlocked, xft_release);
	if (__builtin_expect(val == xft_contested, 1))
		xft_futex_wake(mutex, 1);
}
