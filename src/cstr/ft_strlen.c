/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 02:19:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/08 10:30:16 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_bmi.h"
#include "cstr.h"

#if FT_HAS_512_VEC

__attribute__((pure, __nonnull__(1)))
size_t	ft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u64a						w;
	size_t						offst;
	const t_vu512	*restrict	wp;
	t_vu512a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu512a) - 1));
	wp = (t_blk512r)str;
	w = ft_bitpack512((t_vu512)(wp[0] == 0));
	if (w)
		return (((t_uptr)wp + ft_memctz_u64(w)) - a);
	wp = (t_blk512r)(str + offst);
	while (1)
	{
		mask = (t_vu512a)(((t_blk512ra)wp)[0] == 0);
		w = ft_bitpack512(mask);
		if (w)
			return (((t_uptr)wp + ft_memctz_u64(w)) - a);
		++wp;
	}
}

#elif FT_HAS_256_VEC

__attribute__((pure, __nonnull__(1)))
size_t	ft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u32a						w;
	size_t						offst;
	const t_vu256	*restrict	wp;
	t_vu256a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu256a) - 1));
	wp = (t_blk256r)str;
	w = ft_bitpack256((t_vu256)(wp[0] == 0));
	if (w)
		return (((t_uptr)wp + ft_memctz_u32(w)) - a);
	wp = (t_blk256r)(str + offst);
	while (1)
	{
		mask = (t_vu256a)(((t_blk256ra)wp)[0] == 0);
		w = ft_bitpack256(mask);
		if (w)
			return (((t_uptr)wp + ft_memctz_u32(w)) - a);
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
	const t_vu128	*restrict	wp;
	t_vu128a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu128a) - 1));
	wp = (t_blk128r)str;
	w = ft_bitpack128((t_vu128)(wp[0] == 0));
	if (w)
		return (((t_uptr)wp + ft_memctz_u16(w)) - a);
	wp = (t_blk128r)(str + offst);
	while (1)
	{
		mask = (t_vu128a)(((t_blk128ra)wp)[0] == 0);
		w = ft_bitpack128(mask);
		if (w)
			return (((t_uptr)wp + ft_memctz_u16(w)) - a);
		++wp;
	}
}

#endif
