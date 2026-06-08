/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __max.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 02:10:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/13 19:01:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

t_u128	ft_maxu128(t_u128 x, t_u128 y)
{
	t_u128	cnd;

	cnd = -(x < y);
	return ((cnd & y) | (~cnd & x));
}

t_u64	ft_maxu64(t_u64 x, t_u64 y)
{
	t_u64	cnd;

	cnd = -(x < y);
	return ((cnd & y) | (~cnd & x));
}

t_u32	ft_maxu32(t_u32 x, t_u32 y)
{
	t_u32	cnd;

	cnd = -(x < y);
	return ((cnd & y) | (~cnd & x));
}

t_u8	ft_maxu8(t_u8 x, t_u8 y)
{
	t_u8	cnd;

	cnd = -(x < y);
	return ((cnd & y) | (~cnd & x));
}
