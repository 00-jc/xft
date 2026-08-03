/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((const, __nonnull__(1), __returns_nonnull__))
t_any	ft_align_fwd(t_any ptr, const t_size align)
{
	return ((t_any)(((t_uptr)ptr + align - 1) & ~(align - 1)));
}

__attribute__((const, __nonnull__(1), __returns_nonnull__))
t_any	ft_align_bkw(t_any ptr, const t_size align)
{
	return ((t_any)((t_uptr)ptr & ~(align - 1)));
}
