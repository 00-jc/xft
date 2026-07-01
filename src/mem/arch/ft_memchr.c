/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if FT_HAS_512_VEC

__attribute__((__nonnull__ (1), pure))
void	*ft_memchr(const void *restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu512a))
		return (ft_memchr_avx512(ptr, c, n));
	else if (n >= sizeof(t_vu256a))
		return (ft_memchr_avx256(ptr, c, n));
	else if (n >= sizeof(t_vu128a))
		return (ft_memchr_sse(ptr, c, n));
	else
		return (ft_memchr_minimal(ptr, (t_u8)c, n));
}

#elif FT_HAS_256_VEC

__attribute__((__nonnull__ (1), pure))
void	*ft_memchr(const void *restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu256a))
		return (ft_memchr_avx256(ptr, c, n));
	else if (n >= sizeof(t_vu128a))
		return (ft_memchr_sse(ptr, c, n));
	else
		return (ft_memchr_minimal(ptr, (t_u8)c, n));
}

#else

__attribute__((__nonnull__ (1), pure))
void	*ft_memchr(const void *restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu128a))
		return (ft_memchr_sse(ptr, c, n));
	else
		return (ft_memchr_minimal(ptr, (t_u8)c, n));
}

#endif
