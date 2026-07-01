/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_ctype.h"

__attribute__((const, __always_inline__, hot))
inline t_u16a	ft_isascii128(t_vu128a c)
{
	return (ft_bitpack128((t_vu128a)((c & 0x80) == 0)));
}

#if FT_HAS_256_VEC

__attribute__((const, __always_inline__, hot))
inline t_u32a	ft_isascii256(t_vu256a c)
{
	return (ft_bitpack256((t_vu256a)((c & 0x80) == 0)));
}

#endif

#if FT_HAS_512_VEC

__attribute__((const, __always_inline__, hot))
inline t_u64a	ft_isascii512(t_vu512a c)
{
	return (ft_bitpack512((t_vu512a)((c & 0x80) == 0)));
}

#endif
