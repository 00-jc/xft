/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefetch_noop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

#ifndef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch0(const void *restrict const ptr,
	t_size distance)
{
	(void)ptr;
	(void)distance;
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch1(const void *restrict const ptr,
	t_size distance)
{
	(void)ptr;
	(void)distance;
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch2(const void *restrict const ptr,
	t_size distance)
{
	(void)ptr;
	(void)distance;
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetchnta(const void *restrict const ptr,
	t_size distance)
{
	(void)ptr;
	(void)distance;
}

#endif
