/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_murmur_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:35:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/21 21:36:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hash.h"

__attribute__((const, __always_inline__))
inline t_u64a	rotl(t_u64a x, t_size r)
{
	return ((x << r) | (x >> (64 - r)));
}

__attribute__((const, __always_inline__))
inline t_u64a	fmix64(t_u64a k)
{
	k ^= k >> 33;
	k *= 0xFF51AFD7ED558CCDULL;
	k ^= k >> 33;
	k *= 0xC4CEB9FE1A85EC53ULL;
	k ^= k >> 33;
	return (k);
}
