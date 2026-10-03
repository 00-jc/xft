/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memmove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/02 22:39:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __hot__))
void	xft_memmove(t_any dest, t_cany src, t_size n)
{
	if (__builtin_expect(dest == src || n == 0, 0))
		return ;
	if (n < 8)
		xft_memmove_naive(dest, src, n);
	else if (n < 16)
		xft_memmove_64(dest, src, n);
	else if (n < 32)
		xft_memmove_128(dest, src, n);
	else if (n < 64)
		xft_memmove_256(dest, src, n);
	else if (n < 128)
		xft_memmove_512(dest, src, n);
	else
		xft_memmove_512_huge(dest, src, n);
}
