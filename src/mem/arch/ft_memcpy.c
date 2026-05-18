/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:55:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 20:30:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_naive(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	t_u8	i[7];
	t_u8	s[7];

	i[0] = 0;
	i[1] = -(1ULL < n) & 1;
	i[2] = -(2ULL < n) & 2;
	i[3] = -(3ULL < n) & 3;
	i[4] = -(4ULL < n) & 4;
	i[5] = -(5ULL < n) & 5;
	i[6] = -(6ULL < n) & 6;
	s[0] = ((t_blk8r)src)[i[0]];
	s[1] = ((t_blk8r)src)[i[1]];
	s[2] = ((t_blk8r)src)[i[2]];
	s[3] = ((t_blk8r)src)[i[3]];
	s[4] = ((t_blk8r)src)[i[4]];
	s[5] = ((t_blk8r)src)[i[5]];
	s[6] = ((t_blk8r)src)[i[6]];
	((t_blk8w)dest)[i[0]] = s[0];
	((t_blk8w)dest)[i[1]] = s[1];
	((t_blk8w)dest)[i[2]] = s[2];
	((t_blk8w)dest)[i[3]] = s[3];
	((t_blk8w)dest)[i[4]] = s[4];
	((t_blk8w)dest)[i[5]] = s[5];
	((t_blk8w)dest)[i[6]] = s[6];
}

__attribute__((__nonnull__(1, 2), __hot__))
void	ft_memcpy(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	if (__builtin_expect(dest == src || n == 0, 0))
		return ;
	else if (n < 8)
		ft_memcpy_naive(dest, src, n);
	else if (n < 16)
		ft_memcpy_64(dest, src, n);
	else if (n < 32)
		ft_memcpy_128(dest, src, n);
	else if (n < 64)
		ft_memcpy_256(dest, src, n);
	else if (n < 128)
		ft_memcpy_512(dest, src, n);
	else
		ft_memcpy_512_huge(dest, src, n);
}
