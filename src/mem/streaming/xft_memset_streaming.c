/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memset_streaming.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_mem.h>

__attribute__((__nonnull__(1), __always_inline__, __hot__, __used__))
static inline void	xft__setkernel_stream(t_vu512a *restrict d, t_vu512a x)
{
	__builtin_nontemporal_store(x, d + 0);
	__builtin_nontemporal_store(x, d + 1);
	__builtin_nontemporal_store(x, d + 2);
	__builtin_nontemporal_store(x, d + 3);
	__builtin_nontemporal_store(x, d + 4);
	__builtin_nontemporal_store(x, d + 5);
	__builtin_nontemporal_store(x, d + 6);
	__builtin_nontemporal_store(x, d + 7);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
static inline void	xft_memset_stream_tail(t_any restrict dest,
	t_vu512a x, t_size n)
{
	if (__builtin_expect(63 < n, 1))
	{
		((t_blk512wa)dest)[0] = x;
		((t_blk512wa)dest)[-(128ULL < n) & 1] = x;
		((t_blk512wa)dest)[-(192ULL < n) & 2] = x;
		((t_blk512wa)dest)[-(256ULL < n) & 3] = x;
		((t_blk512wa)dest)[-(320ULL < n) & 4] = x;
		((t_blk512wa)dest)[-(384ULL < n) & 5] = x;
		((t_blk512wa)dest)[-(448ULL < n) & 6] = x;
		((t_blk512wa)dest)[-(512ULL < n) & 7] = x;
	}
	if (__builtin_expect(n != 0, 1))
		*((t_blk512w)xft_overlap(dest, sizeof(t_vu512a), n)) = x;
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_memset_512_streaming(t_any restrict dest,
	const t_u8 c, t_size n)
{
	t_size		delta;
	t_vu512a	*d;
	t_vu512a	x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = x;
	d = (t_vu512a *)((t_u8 *)dest + delta);
	n -= delta;
	while (n >= 512)
	{
		xft__setkernel_stream(d, x);
		d += 8;
		n -= 512;
	}
	xft_stfence();
	xft_memset_stream_tail(d, x, n);
}
