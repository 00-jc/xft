/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 02:19:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 18:13:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_bmi.h"
#include "cstr.h"

#ifdef __AVX512F__

__attribute__((pure, __nonnull__(1)))
size_t	ft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u64a						w;
	size_t						offst;
	const t_vu512a	*restrict	wp;
	t_vu512a					mask;

	a = (t_uptr)str;
	while (*str && ((t_uptr)str & (sizeof(t_vu512a) - 1)))
		++str;
	if (!*str)
		return ((t_uptr)str - a);
	wp = (t_blk512r)str;
	while (1)
	{
		mask = wp[0] == 0;
		w = ft_bitpack512(mask);
		if (w)
		{
			offst = ft_memctz_u64(w);
			return (((t_uptr)wp + offst) - a);
		}
		++wp;
	}
}

#elif defined(__AVX2__)

__attribute__((pure, __nonnull__(1)))
size_t	ft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u32a						w;
	size_t						offst;
	const t_vu256a	*restrict	wp;
	t_vu256a					mask;

	a = (t_uptr)str;
	while (*str && ((t_uptr)str & (sizeof(t_vu256a) - 1)))
		++str;
	if (!*str)
		return ((t_uptr)str - a);
	wp = (t_blk256r)str;
	while (1)
	{
		mask = wp[0] == 0;
		w = ft_bitpack256(mask);
		if (w)
		{
			offst = ft_memctz_u32(w);
			return (((t_uptr)wp + offst) - a);
		}
		++wp;
	}
}

#else

__attribute__((pure, __nonnull__(1)))
size_t	ft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u16a						w;
	size_t						offst;
	const t_vu128a	*restrict	wp;
	t_vu128a					mask;

	a = (t_uptr)str;
	while (*str && ((t_uptr)str & (sizeof(t_vu128a) - 1)))
		++str;
	if (!*str)
		return ((t_uptr)str - a);
	wp = (t_blk128r)str;
	while (1)
	{
		mask = wp[0] == 0;
		w = ft_bitpack128(mask);
		if (w)
		{
			offst = ft_memctz_u16(w);
			return (((t_uptr)wp + offst) - a);
		}
		++wp;
	}
}

#endif
