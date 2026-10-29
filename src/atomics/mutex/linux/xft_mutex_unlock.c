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

#include <xft/mem.h>
#include <xft/atomics.h>
#include <stdatomic.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1), __used__))
inline void	xft_mutex_unlock(t_mutex *__restrict__ const mutex)
{
	t_i32				val;

	xft_prefetch_write0((t_any)mutex, sizeof(*mutex));
	val = atomic_fetch_sub_explicit(mutex, 1, xft_release);
	if (__builtin_expect(val == xft_contested, 1))
	{
		atomic_store_explicit(mutex, xft_unlocked, xft_release);
		xft_futex_wake((t_any)mutex, xft_locked);
	}
}

#endif
