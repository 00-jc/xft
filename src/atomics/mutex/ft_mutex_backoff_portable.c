/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_backoff_portable.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_atomics.h"

#if !defined(__x86_64__) && !defined(__aarch64__)

__attribute__((__always_inline__))
inline void	ft_mutex_backoff(t_u64 n)
{
	while (n--)
		__asm__ volatile ("" ::: "memory");
}

#endif
