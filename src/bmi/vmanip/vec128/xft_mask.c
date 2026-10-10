/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_mask.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:36:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_128_VEC
# if defined(__x86_64__)

__attribute__((__always_inline__, const, __used__))
inline t_u16a	xft_vmask128(t_vu128 vec)
{
	return ((t_u16a)__builtin_ia32_pmovmskb128((t_vc128)vec));
}

# else

__attribute__((__always_inline__, const, __used__))
inline t_u16a	xft_vmask128(t_vu128 vec)
{
	static const t_vu128a	weights = {
		1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128};
	t_u32a					lo;
	t_u32a					hi;

	__asm__ (
		"sshr v0.16b, %[v].16b, #7\n\t"
		"and  v0.16b, v0.16b, %[m].16b\n\t"
		"ext  v1.16b, v0.16b, v0.16b, #8\n\t"
		"addv b0, v0.8b\n\t"
		"addv b1, v1.8b\n\t"
		"umov %w[lo], v0.b[0]\n\t"
		"umov %w[hi], v1.b[0]"
		: [lo] "=r"(lo), [hi] "=r"(hi)
		: [v] "w"(vec), [m] "w"(weights)
		: "v0", "v1"
		);
	return ((t_u16a)(lo | (hi << 8)));
}

# endif
#endif
