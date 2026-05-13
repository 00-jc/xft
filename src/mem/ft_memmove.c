/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 05:35:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((__nonnull__(1, 2), __returns_nonnull__))
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	t_u8		*bd;
	const t_u8	*bs;

	if (dest == src || n == 0)
		return (dest);
	bd = (t_u8 *)dest;
	bs = (const t_u8 *)src;
	if (bd < bs)
		ft_memcpy(dest, src, n);
	else
	{
		bd += n;
		bs += n;
		while (n-- > 0)
			*--bd = *--bs;
	}
	return (dest);
}
