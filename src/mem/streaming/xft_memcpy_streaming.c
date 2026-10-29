/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy_streaming.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 03:24:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_mem.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__, __used__))
static inline void	xft__cpykernel_stream(t_vu512a *restrict d,
	const t_vu512 *restrict s)
{
	__builtin_nontemporal_store(s[0], d + 0);
	__builtin_nontemporal_store(s[1], d + 1);
	__builtin_nontemporal_store(s[2], d + 2);
	__builtin_nontemporal_store(s[3], d + 3);
	__builtin_nontemporal_store(s[4], d + 4);
	__builtin_nontemporal_store(s[5], d + 5);
	__builtin_nontemporal_store(s[6], d + 6);
	__builtin_nontemporal_store(s[7], d + 7);
}

__attribute__((__always_inline__, __nonnull__(1, 2), __used__))
static inline void	xft_memcpy_stream_tail(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	t_vu512a	x[8];

	if (__builtin_expect(63 < n, 1))
	{
		x[0] = ((t_blk512r)src)[0];
		x[1] = ((t_blk512r)src)[-(128ULL < n) & 1];
		x[2] = ((t_blk512r)src)[-(192ULL < n) & 2];
		x[3] = ((t_blk512r)src)[-(256ULL < n) & 3];
		x[4] = ((t_blk512r)src)[-(320ULL < n) & 4];
		x[5] = ((t_blk512r)src)[-(384ULL < n) & 5];
		x[6] = ((t_blk512r)src)[-(448ULL < n) & 6];
		x[7] = ((t_blk512r)src)[-(512ULL < n) & 7];
		((t_blk512wa)dest)[0] = x[0];
		((t_blk512wa)dest)[-(128ULL < n) & 1] = x[1];
		((t_blk512wa)dest)[-(192ULL < n) & 2] = x[2];
		((t_blk512wa)dest)[-(256ULL < n) & 3] = x[3];
		((t_blk512wa)dest)[-(320ULL < n) & 4] = x[4];
		((t_blk512wa)dest)[-(384ULL < n) & 5] = x[5];
		((t_blk512wa)dest)[-(448ULL < n) & 6] = x[6];
		((t_blk512wa)dest)[-(512ULL < n) & 7] = x[7];
	}
	if (__builtin_expect(n != 0, 1))
		*((t_blk512w)xft_overlap(dest, sizeof(t_vu512a), n)) =
			*((t_blk512r)xft_overlap(src, sizeof(t_vu512a), n));
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memcpy_512_streaming(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	t_size			delta;
	t_vu512a		*d;
	const t_vu512	*s;

	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = *(t_blk512r)src;
	d = (t_vu512a *)((t_u8 *)dest + delta);
	s = (const t_vu512 *)((const t_u8 *)src + delta);
	n -= delta;
	while (n >= 512)
	{
		xft__cpykernel_stream(d, s);
		d += 8;
		s += 8;
		n -= 512;
	}
	xft_stfence();
	xft_memcpy_stream_tail(d, s, n);
}
