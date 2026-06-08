/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 17:19:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_ctype.h"

__attribute__((const, __always_inline__, hot))
inline t_u16a	ft_isprint128(t_vu128a c)
{
	return (ft_bitpack128((t_vu128a)((c - 0x20) < 0x5F)));
}

#if FT_HAS_256_VEC

__attribute__((const, __always_inline__, hot))
inline t_u32a	ft_isprint256(t_vu256a c)
{
	return (ft_bitpack256((t_vu256a)((c - 0x20) < 0x5F)));
}

#endif

#if FT_HAS_512_VEC

__attribute__((const, __always_inline__, hot))
inline t_u64a	ft_isprint512(t_vu512a c)
{
	return (ft_bitpack512((t_vu512a)((c - 0x20) < 0x5F)));
}

#endif
