/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_cache_line_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 22:10:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_rt.h>

#if defined(__x86_64__) || defined(__i386__)

# include <cpuid.h>

__attribute__((const, __always_inline__, __used__))
inline t_u32a	xft_cache_line_size(void)
{
	t_u32	r[4];

	__cpuid(1, r[0], r[1], r[2], r[3]);
	return (((r[1] >> 8) & 0xff) * 8);
}

#endif
