/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/05 22:34:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_bmi.h"
#include "cstr.h"

#if XFT_HAS_512_VEC

__attribute__((pure, __nonnull__(1), __no_sanitize_address__))
t_size	xft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u64a						w;
	t_size						offst;
	const t_vu512	*restrict	wp;
	t_vu512a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu512a) - 1));
	wp = (t_blk512r)str;
	w = xft_bitpack512((t_vu512)(wp[0] == 0));
	if (__builtin_expect(w != 0, 1))
		return (((t_uptr)wp + xft_memctz_u64(w)) - a);
	wp = (t_blk512r)(str + offst);
	while (1)
	{
		mask = (t_vu512a)(((t_blk512ra)wp)[0] == 0);
		w = xft_bitpack512(mask);
		if (__builtin_expect(w != 0, 1))
			return (((t_uptr)wp + xft_memctz_u64(w)) - a);
		++wp;
	}
}

#elif XFT_HAS_256_VEC

__attribute__((pure, __nonnull__(1), __no_sanitize_address__))
t_size	xft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u32a						w;
	t_size						offst;
	const t_vu256	*restrict	wp;
	t_vu256a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu256a) - 1));
	wp = (t_blk256r)str;
	w = xft_bitpack256((t_vu256)(wp[0] == 0));
	if (__builtin_expect(w != 0, 1))
		return (((t_uptr)wp + xft_memctz_u32(w)) - a);
	wp = (t_blk256r)(str + offst);
	while (1)
	{
		mask = (t_vu256a)(((t_blk256ra)wp)[0] == 0);
		w = xft_bitpack256(mask);
		if (__builtin_expect(w != 0, 1))
			return (((t_uptr)wp + xft_memctz_u32(w)) - a);
		++wp;
	}
}

#else

__attribute__((pure, __nonnull__(1), __no_sanitize_address__))
t_size	xft_strlen(const char *restrict str)
{
	t_uptr						a;
	t_u16a						w;
	t_size						offst;
	const t_vu128	*restrict	wp;
	t_vu128a					mask;

	a = (t_uptr)str;
	offst = ((-(t_uptr)str) & (sizeof(t_vu128a) - 1));
	wp = (t_blk128r)str;
	w = xft_bitpack128((t_vu128)(wp[0] == 0));
	if (__builtin_expect(w != 0, 1))
		return (((t_uptr)wp + xft_memctz_u16(w)) - a);
	wp = (t_blk128r)(str + offst);
	while (1)
	{
		mask = (t_vu128a)(((t_blk128ra)wp)[0] == 0);
		w = xft_bitpack128(mask);
		if (__builtin_expect(w != 0, 1))
			return (((t_uptr)wp + xft_memctz_u16(w)) - a);
		++wp;
	}
}

#endif
