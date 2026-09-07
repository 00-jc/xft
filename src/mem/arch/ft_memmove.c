/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/02 22:39:33 by jaicastr         ###   ########.fr       */
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
void	ft_memmove(t_any dest, t_cany src, t_size n)
{
	if (__builtin_expect(dest == src || n == 0, 0))
		return ;
	if (n < 8)
		ft_memmove_naive(dest, src, n);
	else if (n < 16)
		ft_memmove_64(dest, src, n);
	else if (n < 32)
		ft_memmove_128(dest, src, n);
	else if (n < 64)
		ft_memmove_256(dest, src, n);
	else if (n < 128)
		ft_memmove_512(dest, src, n);
	else
		ft_memmove_512_huge(dest, src, n);
}
