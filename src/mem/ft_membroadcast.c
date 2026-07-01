/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_membroadcast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((__nonnull__(1, 2)))
void	ft_membroadcast(void *dst, void *src, t_size chunk_size, t_size n)
{
	t_u8	*d;

	if (!chunk_size || !n)
		return ;
	d = (t_u8 *)dst;
	while (n-- > 0)
	{
		ft_memcpy(d, src, chunk_size);
		d += chunk_size;
	}
}
