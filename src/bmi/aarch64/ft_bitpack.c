/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitpack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 22:09:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_bmi.h"

#if defined(__aarch64__) && FT_HAS_128_VEC

/*
 *	Gated on FT_HAS_128_VEC (not just __aarch64__): this is real NEON
 *	asm, so it must not build on an aarch64 target compiled without
 *	NEON (e.g. -mgeneral-regs-only).
 *
 *	NEON has no pmovmskb-equivalent instruction, so the 16 lanes (each
 *	0x00 or 0xFF from a comparison) are ANDed against their bit weight
 *	{1,2,4,...,128} twice over, split into two 8-lane halves, and each
 *	half is folded down with three pairwise-add passes until lane 0
 *	holds the OR (== sum, since the weight bits never overlap) of its
 *	8 lanes. That gives one byte of the mask per half; umov extracts
 *	them into general registers to be combined. v0/v1 are reserved as
 *	scratch via the clobber list so the register allocator is free to
 *	place %[v]/%[m] anywhere else.
 *
 *	Only the 128-bit width exists here: NEON is a fixed 128-bit ISA, so
 *	FT_HAS_256_VEC / FT_HAS_512_VEC are never set on aarch64 (see
 *	private/ft_p_asm.h) and ft_bitpack256/512 are unreachable.
 */

__attribute__((const, __always_inline__))
inline t_u16a	ft_bitpack128(t_vu128a vec)
{
	static const t_vu128a	weights = (t_vu128a)
	{1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128};
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
