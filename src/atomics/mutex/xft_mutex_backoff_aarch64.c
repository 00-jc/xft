/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mutex_backoff_aarch64.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_atomics.h"

#ifdef __aarch64__

__attribute__((__always_inline__, __used__))
inline void	xft_mutex_backoff(t_u64 n)
{
	while (n--)
		__asm__ volatile ("yield" ::: "memory");
}

#endif
