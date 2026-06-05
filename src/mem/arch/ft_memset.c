/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/02 18:36:48 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_naive(void *restrict dest,
	const t_u8 b, size_t n)
{
	t_u8	i[7];

	i[0] = 0;
	i[1] = -(1ULL < n) & 1;
	i[2] = -(2ULL < n) & 2;
	i[3] = -(3ULL < n) & 3;
	i[4] = -(4ULL < n) & 4;
	i[5] = -(5ULL < n) & 5;
	i[6] = -(6ULL < n) & 6;
	((t_blk8w)dest)[i[0]] = b;
	((t_blk8w)dest)[i[1]] = b;
	((t_blk8w)dest)[i[2]] = b;
	((t_blk8w)dest)[i[3]] = b;
	((t_blk8w)dest)[i[4]] = b;
	((t_blk8w)dest)[i[5]] = b;
	((t_blk8w)dest)[i[6]] = b;
}

__attribute__((__nonnull__(1), __hot__))
void	ft_memset(void *restrict dest,
	const t_u8 b, size_t n)
{
	if (__builtin_expect(n == 0, 0))
		return ;
	else if (n < 8)
		ft_memset_naive(dest, b, n);
	else if (n < 16)
		ft_memset_64(dest, b, n);
	else if (n < 32)
		ft_memset_128(dest, b, n);
	else if (n < 64)
		ft_memset_256(dest, b, n);
	else if (n < 128)
		ft_memset_512(dest, b, n);
	else if (n < FT_LLC_SIZE)
		ft_memset_512_huge(dest, b, n);
	else
		ft_memset_512_streaming(dest, b, n);
}
