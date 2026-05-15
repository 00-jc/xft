/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:21:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 20:56:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if defined(__AVX512VL__)

__attribute__((__nonnull__(1, 2)))
ssize_t	ft_memcmp(const void *restrict const dest,
	const void *restrict src, size_t n)
{
	if (n >= sizeof(t_vu512a))
		return (ft_memcmp_avx512(dest, src, n));
	else if (n >= sizeof(t_vu256a))
		return (ft_memcmp_avx256(dest, src, n));
	else if (n >= sizeof(t_vu128a))
		return (ft_memcmp_sse(dest, src, n));
	else
		return (ft_memcmp_minimal(dest, src, 0, n));
}

#elif defined(__AVX2__)

__attribute__((__nonnull__(1, 2)))
ssize_t	ft_memcmp(const void *restrict const dest,
	const void *restrict src, size_t n)
{
	if (n >= sizeof(t_vu256a))
		return (ft_memcmp_avx256(dest, src, n));
	else if (n >= sizeof(t_vu128a))
		return (ft_memcmp_sse(dest, src, n));
	else
		return (ft_memcmp_minimal(dest, src, 0, n));
}

#else

__attribute__((__nonnull__(1, 2)))
ssize_t	ft_memcmp(const void *restrict const dest,
	const void *restrict src, size_t n)
{
	if (n >= sizeof(t_vu128a))
		return (ft_memcmp_sse(dest, src, n));
	else
		return (ft_memcmp_minimal(dest, src, 0, n));
}

#endif
