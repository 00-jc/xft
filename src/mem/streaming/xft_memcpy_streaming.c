/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy_streaming.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 12:05:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if defined (__x86_64__) && XFT_HAS_512_VEC

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__, __used__))
inline void	xft__cpykernel_stream(t_any restrict d,
	t_cany restrict const s, t_size offset)
{
	t_vu512a	*restrict	pd;
	t_vu512a	*restrict	ps;

	pd = (t_blk512wa)((t_u8 *)d + (offset << 6));
	ps = (t_blk512w)((const t_u8 *)s + (offset << 6));
	__asm__ (
		"vmovdqu64 %4, %%zmm0\n" "vmovdqu64 %5, %%zmm1\n"
		"vmovdqu64 %6, %%zmm2\n" "vmovdqu64 %7, %%zmm3\n"
		"vmovntdq %%zmm0, %0\n" "vmovntdq %%zmm1, %1\n"
		"vmovntdq %%zmm2, %2\n" "vmovntdq %%zmm3, %3"
		: "=m"(pd[0]), "=m"(pd[1]), "=m"(pd[2]), "=m"(pd[3])
		: "m"(ps[0]), "m"(ps[1]), "m"(ps[2]), "m"(ps[3])
		: "zmm0", "zmm1", "zmm2", "zmm3", "memory"
		);
	__asm__ (
		"vmovdqu64 %4, %%zmm0\n" "vmovdqu64 %5, %%zmm1\n"
		"vmovdqu64 %6, %%zmm2\n" "vmovdqu64 %7, %%zmm3\n"
		"vmovntdq %%zmm0, %0\n" "vmovntdq %%zmm1, %1\n"
		"vmovntdq %%zmm2, %2\n" "vmovntdq %%zmm3, %3"
		: "=m"(pd[4]), "=m"(pd[5]), "=m"(pd[6]), "=m"(pd[7])
		: "m"(ps[4]), "m"(ps[5]), "m"(ps[6]), "m"(ps[7])
		: "zmm0", "zmm1", "zmm2", "zmm3", "memory"
		);
}

#elif defined(__x86_64__) && XFT_HAS_256_VEC

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__, __used__))
inline void	xft__cpykernel_stream(t_any restrict d,
	t_cany restrict const s, t_size offset)
{
	t_vu256a		*restrict	pd;
	const t_vu256	*restrict	ps;

	pd = (t_blk256wa)((t_u8 *)d + (offset << 6));
	ps = (t_blk256r)((const t_u8 *)s + (offset << 6));
	__asm__ (
		"vmovdqu 0x000(%[s]), %%ymm0\n" "vmovdqu 0x020(%[s]), %%ymm1\n"
		"vmovdqu 0x040(%[s]), %%ymm2\n" "vmovdqu 0x060(%[s]), %%ymm3\n"
		"vmovntdq %%ymm0, 0x000(%[d])\n" "vmovntdq %%ymm1, 0x020(%[d])\n"
		"vmovntdq %%ymm2, 0x040(%[d])\n" "vmovntdq %%ymm3, 0x060(%[d])\n"
		"vmovdqu 0x080(%[s]), %%ymm0\n" "vmovdqu 0x0a0(%[s]), %%ymm1\n"
		"vmovdqu 0x0c0(%[s]), %%ymm2\n" "vmovdqu 0x0e0(%[s]), %%ymm3\n"
		"vmovntdq %%ymm0, 0x080(%[d])\n" "vmovntdq %%ymm1, 0x0a0(%[d])\n"
		"vmovntdq %%ymm2, 0x0c0(%[d])\n" "vmovntdq %%ymm3, 0x0e0(%[d])\n"
		"vmovdqu 0x100(%[s]), %%ymm0\n" "vmovdqu 0x120(%[s]), %%ymm1\n"
		"vmovdqu 0x140(%[s]), %%ymm2\n" "vmovdqu 0x160(%[s]), %%ymm3\n"
		"vmovntdq %%ymm0, 0x100(%[d])\n" "vmovntdq %%ymm1, 0x120(%[d])\n"
		"vmovntdq %%ymm2, 0x140(%[d])\n" "vmovntdq %%ymm3, 0x160(%[d])\n"
		"vmovdqu 0x180(%[s]), %%ymm0\n" "vmovdqu 0x1a0(%[s]), %%ymm1\n"
		"vmovdqu 0x1c0(%[s]), %%ymm2\n" "vmovdqu 0x1e0(%[s]), %%ymm3\n"
		"vmovntdq %%ymm0, 0x180(%[d])\n" "vmovntdq %%ymm1, 0x1a0(%[d])\n"
		"vmovntdq %%ymm2, 0x1c0(%[d])\n" "vmovntdq %%ymm3, 0x1e0(%[d])"
		:: [d] "r"(pd), [s] "r"(ps)
		: "ymm0", "ymm1", "ymm2", "ymm3", "memory"
		);
}

#else

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__, __used__))
inline void	xft__cpykernel_stream(t_any restrict d,
	t_cany restrict const s, t_size offset)
{
	t_vu512a	x[8];

	x[0] = ((t_blk512r)s)[offset + 0];
	x[1] = ((t_blk512r)s)[offset + 1];
	x[2] = ((t_blk512r)s)[offset + 2];
	x[3] = ((t_blk512r)s)[offset + 3];
	x[4] = ((t_blk512r)s)[offset + 4];
	x[5] = ((t_blk512r)s)[offset + 5];
	x[6] = ((t_blk512r)s)[offset + 6];
	x[7] = ((t_blk512r)s)[offset + 7];
	((t_blk512wa)d)[offset + 0] = x[0];
	((t_blk512wa)d)[offset + 1] = x[1];
	((t_blk512wa)d)[offset + 2] = x[2];
	((t_blk512wa)d)[offset + 3] = x[3];
	((t_blk512wa)d)[offset + 4] = x[4];
	((t_blk512wa)d)[offset + 5] = x[5];
	((t_blk512wa)d)[offset + 6] = x[6];
	((t_blk512wa)d)[offset + 7] = x[7];
}

#endif

__attribute__((__always_inline__, __nonnull__(1, 2), __used__))
inline void	xft_memcpy_stream_tail(t_any restrict dest,
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
	t_t_f64_size	s;
	t_size			delta;
	t_u8			*d;
	const t_u8		*sr;

	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = *(t_blk512r)src;
	d = (t_u8 *)dest + delta;
	sr = (const t_u8 *)src + delta;
	n -= delta;
	s.blks = (n >> 6);
	s.i = 0;
	while (s.i + 8 <= s.blks)
	{
		xft__cpykernel_stream(d, sr, s.i);
		s.i += 8;
	}
	xft_stfence();
	xft_memcpy_stream_tail(d + (s.i << 6), sr + (s.i << 6), n - (s.i << 6));
}
