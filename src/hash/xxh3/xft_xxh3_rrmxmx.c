/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_xxh3_rrmxmx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_xxh3.h"

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_xxh3_rrmxmx(t_u64a a, t_u64a b)
{
	a ^= xft_rotl64(a, 49) ^ xft_rotl64(a, 24);
	a *= XXH3_PRIME_MX2;
	a ^= (a >> 35) + b;
	a *= XXH3_PRIME_MX2;
	return (xft_xxh3_xorshift64(a, 28));
}
