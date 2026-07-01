/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_finalizers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_mix2accs(t_blk64w acc, const t_u8 *secret)
{
	return (ft_xxh3_mul128_fold64(
			acc[0] ^ *(t_blk64r)secret,
			acc[1] ^ *(t_blk64r)(secret + 8)));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_merge_accs(t_blk64w acc, const t_u8 *secret,
	t_u64 start)
{
	t_u64	result;

	result = start;
	result += ft_xxh3_mix2accs(acc + (0 << 1), secret + (0 << 4));
	result += ft_xxh3_mix2accs(acc + (1 << 1), secret + (1 << 4));
	result += ft_xxh3_mix2accs(acc + (2 << 1), secret + (2 << 4));
	result += ft_xxh3_mix2accs(acc + (3 << 1), secret + (3 << 4));
	return (ft_xxh3_avalanche(result));
}
