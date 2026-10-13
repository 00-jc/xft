/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_to_le_from_be.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

__attribute__((__always_inline__, __used__))
inline t_u16a	xft_to_le16(t_u16a x)
{
	return (xft_bswap16(x));
}

__attribute__((__always_inline__, __used__))
inline t_u32a	xft_to_le32(t_u32a x)
{
	return (xft_bswap32(x));
}

__attribute__((__always_inline__, __used__))
inline t_u64a	xft_to_le64(t_u64a x)
{
	return (xft_bswap64(x));
}

#endif
