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

#ifdef __aarch64__

__attribute__((const, __always_inline__, __used__))
inline t_u32a	xft_cache_line_size(void)
{
	t_u64a	ctr;

	__asm__ ("mrs %0, ctr_el0" : "=r"(ctr));
	return ((t_u32a)(4 << ((ctr >> 16) & 0xf)));
}

#endif
