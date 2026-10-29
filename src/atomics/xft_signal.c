/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 22:16:32 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 22:46:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <stdatomic.h>
#include <stdint.h>

__attribute__((__nonnull__(1), __flatten__, __always_inline__, __used__))
inline void	xft_wait_for_signal(t_atomic32 *__restrict__ const atomic)
{
	const t_u32a	seen = atomic_load_explicit(atomic, xft_acquire);

	while (atomic_load_explicit(atomic, xft_acquire) == seen)
		xft_futex_wait(atomic, seen);
}

__attribute__((__nonnull__(1), __flatten__, __always_inline__, __used__))
inline void	xft_send_signal(t_atomic32 *__restrict__ const atomic)
{
	atomic_fetch_add_explicit(atomic, 1, xft_release);
	xft_futex_wake(atomic, UINT32_MAX);
}
