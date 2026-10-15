/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/16 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if defined(__clang__)

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__,
	__returns_nonnull__))
inline void	*xft_memcpy(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	if (n == 1)
		return (__builtin_memcpy(dest, src, 1));
	if (n == 2)
		return (__builtin_memcpy(dest, src, 2));
	if (n == 4)
		return (__builtin_memcpy(dest, src, 4));
	if (n == 8)
		return (__builtin_memcpy(dest, src, 8));
	if (n == 16)
		return (__builtin_memcpy(dest, src, 16));
	if (n == 32)
		return (__builtin_memcpy(dest, src, 32));
	if (n == 64)
		return (__builtin_memcpy(dest, src, 64));
	if (n == 128)
		return (__builtin_memcpy(dest, src, 128));
	if (n == 256)
		return (__builtin_memcpy(dest, src, 256));
	return (xft__memcpy(dest, src, n));
}

# if !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 2), __hot__, __returns_nonnull__, __weak__))
t_any	memcpy(t_any restrict dest, t_cany restrict const src, t_size n)
{
	return (xft__memcpy(dest, src, n));
}

# endif

#else

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__,
	__returns_nonnull__))
inline void	*xft_memcpy(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	if (__builtin_constant_p(n))
		return (__builtin_memcpy(dest, src, n));
	return (xft__memcpy(dest, src, n));
}

# if !defined(XFT_REQUIRE_LIBC)

t_any	memcpy(t_any restrict dest, t_cany restrict const src, t_size n)\
			__attribute__((__nonnull__(1, 2), __hot__, __returns_nonnull__,\
				__weak__, __alias__("xft_memcpy")));

# endif

#endif
