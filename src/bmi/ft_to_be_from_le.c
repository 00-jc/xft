/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_be_from_le.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ 

__attribute__((__always_inline__))
inline t_u16a	ft_to_be16(t_u16a x)
{
	return (ft_bswap16(x));
}

__attribute__((__always_inline__))
inline t_u32a	ft_to_be32(t_u32a x)
{
	return (ft_bswap32(x));
}

__attribute__((__always_inline__))
inline t_u64a	ft_to_be64(t_u64a x)
{
	return (ft_bswap64(x));
}

#endif
