/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_bitpack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/04 00:32:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_bmi.h"

#if defined(__aarch64__) && XFT_HAS_128_VEC

__attribute__((const, __always_inline__, __used__))
inline t_u16a	xft_bitpack128(t_vu128a vec)
{
	static const t_vu128a	weights = {
		1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128};
	t_u32a					lo;
	t_u32a					hi;

	__asm__ volatile (
		"and  v0.16b, %[v].16b, %[m].16b\n\t"
		"ext  v1.16b, v0.16b, v0.16b, #8\n\t"
		"addp v0.8b, v0.8b, v0.8b\n\t"
		"addp v0.8b, v0.8b, v0.8b\n\t"
		"addp v0.8b, v0.8b, v0.8b\n\t"
		"addp v1.8b, v1.8b, v1.8b\n\t"
		"addp v1.8b, v1.8b, v1.8b\n\t"
		"addp v1.8b, v1.8b, v1.8b\n\t"
		"umov %w[lo], v0.b[0]\n\t"
		"umov %w[hi], v1.b[0]"
		: [lo] "=r"(lo), [hi] "=r"(hi)
		: [v] "w"(vec), [m] "w"(weights)
		: "v0", "v1"
	);
	return ((t_u16a)(lo | (hi << 8)));
}

#endif
