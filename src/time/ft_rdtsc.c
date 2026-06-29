/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdtsc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:21:04 by username          #+#    #+#             */
/*   Updated: 2026/06/28 21:48:36 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "private/ft_p_time.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline t_u64a	ft_rdtsc(void)
{
	ft_ldfence();
	return (__builtin_ia32_rdtsc());
}

#endif
