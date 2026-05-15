/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/13 02:26:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if defined(__AVX512VL__)

__attribute__((__nonnull__(1)))
void	ft_memset(void *restrict dest,
	const t_u8 b, size_t n)
{
	if (n < 8)
		ft_memset_naive(dest, b, n);
	else if (n < 16)
		ft_memset_64(dest, b, n);
	else if (n < 32)
		ft_memset_128(dest, b, n);
	else if (n < 64)
		ft_memset_256(dest, b, n);
	else
		ft_memset_512(dest, b, n);
}

#elif defined(__AVX2__)

__attribute__((__nonnull__(1)))
void	ft_memset(void *restrict dest,
	const t_u8 b, size_t n)
{
	if (n < 8)
		ft_memset_naive(dest, b, n);
	else if (n < 16)
		ft_memset_64(dest, b, n);
	else if (n < 32)
		ft_memset_128(dest, b, n);
	else
		ft_memset_256(dest, b, n);
}

#else

__attribute__((__nonnull__(1)))
void	ft_memset(void *restrict dest,
	const t_u8 b, size_t n)
{
	if (n < 8)
		ft_memset_naive(dest, b, n);
	else if (n < 16)
		ft_memset_64(dest, b, n);
	else
		ft_memset_128(dest, b, n);
}

#endif
