/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "alloc.h"

__attribute__((__nonnull__(1)))
void	*ft_memclone(void *restrict ptr, size_t size)
{
	void	*new_reg;

	if (size == 0)
		return (nullptr);
	new_reg = ft_alloc(size);
	if (!new_reg)
		return (nullptr);
	ft_memmove(new_reg, ptr, size);
	return (new_reg);
}
