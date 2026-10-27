/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_from_be.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>

__attribute__((__always_inline__, __used__))
inline t_u16a	xft_from_be16(t_u16a x)
{
	return (xft_to_be16(x));
}

__attribute__((__always_inline__, __used__))
inline t_u32a	xft_from_be32(t_u32a x)
{
	return (xft_to_be32(x));
}

__attribute__((__always_inline__, __used__))
inline t_u64a	xft_from_be64(t_u64a x)
{
	return (xft_to_be64(x));
}
