/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 21:10:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 21:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_futex_wait(t_atomic32 *__restrict__ const atomic,
	t_u32a value_to_wait)
{
	WaitOnAddress(atomic, &value_to_wait, sizeof(*atomic), INFINITE);
}

#endif
