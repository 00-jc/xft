/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 20:33:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

/*
 * Note: all memcpy variants are
 * 		 overlap-safe except the
 *		 hugebranch, bc of read
 *		 then store policy.
 *
 *		 So we reuse those.
 */

__attribute__((__nonnull__(1, 2), __hot__))
void	ft_memmove(void *restrict dest, const void *restrict src, size_t n)
{
	if (__builtin_expect(dest == src || n == 0, 0))
		return ;
	if (n < 8)
		ft_memcpy_naive(dest, src, n);
	else if (n < 16)
		ft_memcpy_64(dest, src, n);
	else if (n < 32)
		ft_memcpy_128(dest, src, n);
	else if (n < 64)
		ft_memcpy_256(dest, src, n);
	else if (n < 128)
		ft_memcpy_512(dest, src, n);
	else if ((t_u8 *)dest <= (t_u8 *)src
		|| (t_u8 *)dest >= (t_u8 *)src + n)
		ft_memcpy_512_huge(dest, src, n);
	else
		ft_memmove_512_huge(dest, src, n);
}
