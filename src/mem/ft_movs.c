/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:01:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 05:12:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_movsb(void *restrict dest,
	const void	*restrict src, size_t n)
{
	__asm__ volatile (
		"rep movsb"
		: "+D"(dest), "+S"(src), "+c"(n)
		:
		: "memory"
	);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_movsq(void *restrict dest,
	const void	*restrict src, size_t qw)
{
	__asm__ volatile (
		"rep movsq"
		: "+D"(dest), "+S"(src), "+c"(qw)
		:
		: "memory"
	);
}

#else

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_movsb(void *restrict dest,
	const void	*restrict src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_blk8w)dest)[i] = ((t_blk8r)src)[i];
		++i;
	}
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_movsq(void *restrict dest,
	const void	*restrict src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_blk64w)dest)[i] = ((t_blk64r)src)[i];
		++i;
	}
}
#endif
