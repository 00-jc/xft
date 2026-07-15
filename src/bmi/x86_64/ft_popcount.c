/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:43:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 12:48:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#ifdef __x86_64__

__attribute__((__const__, __always_inline__))
inline t_u32a	ft_popcount_u32(t_u32a x)
{
	__asm__ ("popcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((__const__, __always_inline__))
inline t_u64a	ft_popcount_u64(t_u64a x)
{
	__asm__ ("popcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

#endif
