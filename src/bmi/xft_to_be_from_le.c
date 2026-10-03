/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_to_be_from_le.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ 

__attribute__((__always_inline__, __used__))
inline t_u16a	xft_to_be16(t_u16a x)
{
	return (xft_bswap16(x));
}

__attribute__((__always_inline__, __used__))
inline t_u32a	xft_to_be32(t_u32a x)
{
	return (xft_bswap32(x));
}

__attribute__((__always_inline__, __used__))
inline t_u64a	xft_to_be64(t_u64a x)
{
	return (xft_bswap64(x));
}

#endif
