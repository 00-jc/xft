/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 05:16:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/17 06:30:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((const, __nonnull__(1), __returns_nonnull__))
void	*ft_align_fwd(void *ptr, const t_size align)
{
	return ((void *)(((t_uptr)ptr + align) & ~align));
}

__attribute__((const, __nonnull__(1), __returns_nonnull__))
void	*ft_align_bkw(void *ptr, const t_size align)
{
	return ((void *)((t_uptr)ptr & ~align));
}
