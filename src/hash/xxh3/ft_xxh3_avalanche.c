/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_avalanche.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

inline t_u64a	ft_xxh3_avalanche(t_u64 hash)
{
	hash = ft_xxh3_xorshift64(hash, 37);
	hash *= XXH3_PRIME_MX1;
	hash = ft_xxh3_xorshift64(hash, 32);
	return (hash);
}

__attribute__((__always_inline__, const))
inline t_u64a	ft_xxh64_avalanche(t_u64 hash)
{
	hash ^= hash >> 33;
	hash *= XXH3_PRIME64_2;
	hash ^= hash >> 29;
	hash *= XXH3_PRIME64_3;
	hash ^= hash >> 32;
	return (hash);
}
