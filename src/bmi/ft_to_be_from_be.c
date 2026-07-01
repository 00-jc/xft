/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_be_from_be.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ 

__attribute__((__always_inline__))
inline t_u16a	ft_to_be16(t_u16a x)
{
	return (x);
}

__attribute__((__always_inline__))
inline t_u32a	ft_to_be32(t_u32a x)
{
	return (x);
}

__attribute__((__always_inline__))
inline t_u64a	ft_to_be64(t_u64a x)
{
	return (x);
}

#endif
