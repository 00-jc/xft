/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get128.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_asm.h"

#ifndef __LIBFT_SCALAR__

__attribute__((const, __always_inline__))
inline t_vu128	get_high128(void)
{
	return ((t_vu128)
		{
			0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
			0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		});
}

__attribute__((const, __always_inline__))
inline t_vu128	get_lones128(void)
{
	return ((t_vu128)
		{
			0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		});
}

__attribute__((const, __always_inline__))
inline t_vu128	get_z128(void)
{
	return ((t_vu128)
		{
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		});
}

__attribute__((const, __always_inline__))
inline t_vu128	get_mask128(t_u8 x)
{
	return ((t_vu128)
		{
			x, x, x, x, x, x, x, x,
			x, x, x, x, x, x, x, x,
		});
}

#endif
