/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_avx512.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 03:43:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 21:28:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_512(void *restrict dest,
	const t_u8 c, size_t n)
{
	register t_vu512a	x;

	x = (t_vu512a){
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c
	};
	*(t_blk512w)dest = x;
	*(t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n) = x;
}
