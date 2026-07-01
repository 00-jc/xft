/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_ctype.h"

__attribute__((const, __always_inline__, hot))
inline t_u16a	ft_isdigit128(t_vu128a c)
{
	return (ft_bitpack128((t_vu128a)((c - '0') < 0xA)));
}

#if FT_HAS_256_VEC

__attribute__((const, __always_inline__, hot))
inline t_u32a	ft_isdigit256(t_vu256a c)
{
	return (ft_bitpack256((t_vu256a)((c - '0') < 0xA)));
}

#endif

#if FT_HAS_512_VEC

__attribute__((const, __always_inline__, hot))
inline t_u64a	ft_isdigit512(t_vu512a c)
{
	return (ft_bitpack512((t_vu512a)((c - '0') < 0xA)));
}

#endif
