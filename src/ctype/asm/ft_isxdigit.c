/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:46:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 17:20:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_ctype.h"

__attribute__((const, __always_inline__, hot))
inline t_u16a	ft_isxdigit128(t_vu128a c)
{
	return (ft_isdigit128(c) | ft_bitpack128((t_vu128a)(((c | 32) - 'a') < 6)));
}

#if FT_HAS_256_VEC

__attribute__((const, __always_inline__, hot))
inline t_u32a	ft_isxdigit256(t_vu256a c)
{
	return (ft_isdigit256(c) | ft_bitpack256((t_vu256a)(((c | 32) - 'a') < 6)));
}

#endif

#if FT_HAS_512_VEC

__attribute__((const, __always_inline__, hot))
inline t_u64a	ft_isxdigit512(t_vu512a c)
{
	return (ft_isdigit512(c) | ft_bitpack512((t_vu512a)(((c | 32) - 'a') < 6)));
}

#endif
