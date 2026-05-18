/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitpack_intrin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:17:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:49:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_bmi.h"

#ifdef __x86_64__

__attribute__((const, __always_inline__))
inline t_u16a	ft_bitpack128(t_vu128a vec)
{
	t_u32a	result;

	__asm__ (
		"pmovmskb %1, %0"
		: "=r" (result)
		: "x" (vec)
		);
	return ((t_u16a)result);
}

# if FT_HAS_256_VEC

__attribute__((const, __always_inline__))
inline t_u32a	ft_bitpack256(t_vu256a vec)
{
	t_u32a		result;

	__asm__ (
		"vpmovmskb %1, %0"
		: "=r" (result)
		: "x" (vec)
		);
	return (result);
}

# endif

# if FT_HAS_512_VEC

__attribute__((const, used, __always_inline__))
inline t_u64a	ft_bitpack512(t_vu512a vec)
{
	t_u64a	result;

	__asm__ (
		"vpmovb2m %1, %0"
		: "=k"(result)
		: "v" (vec)
		);
	return (result);
}

# endif

#endif
