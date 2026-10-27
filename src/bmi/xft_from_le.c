/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_from_le.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>

__attribute__((__always_inline__, __used__))
inline t_u16a	xft_from_le16(t_u16a x)
{
	return (xft_to_le16(x));
}

__attribute__((__always_inline__, __used__))
inline t_u32a	xft_from_le32(t_u32a x)
{
	return (xft_to_le32(x));
}

__attribute__((__always_inline__, __used__))
inline t_u64a	xft_from_le64(t_u64a x)
{
	return (xft_to_le64(x));
}
