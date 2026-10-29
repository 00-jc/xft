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

#include <xft/types/atomic_types.h>
#include <xft/xft_p_atomics.h>
#include <stdatomic.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_mutex_slow(t_mutex *__restrict__ const mutex)
{
	while (true)
	{
		if (__builtin_expect(atomic_exchange_explicit(mutex, xft_contested,
					xft_acq_rel) == xft_unlocked, 1))
			return ;
		WaitOnAddress(mutex, &(t_i32){xft_contested}, sizeof(*mutex), INFINITE);
	}
}

#endif
