/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_streaming.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 23:50:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 04:24:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if defined (__x86_64__) && FT_HAS_512_VEC

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline void	ft__cpykernel_stream(void *restrict d,
	const void *restrict const s, size_t offset)
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

#elif defined(__x86_64__) && FT_HAS_256_VEC

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline void	ft__cpykernel_stream(void *restrict d,
	const void *restrict const s, size_t offset)
{
	t_vu256a	*restrict	pd;
	t_vu256a	*restrict	ps;

	pd = (t_blk256wa)((t_u8 *)d + (offset << 6));
	ps = (t_blk256r)((const t_u8 *)s + (offset << 6));
	__asm__ (
		"vmovdqu %8, %%ymm0\n" "vmovdqu %9, %%ymm1\n" "vmovdqu %10, %%ymm2\n"
		"vmovdqu %11, %%ymm3\n" "vmovntdq %%ymm0, %0\n" "vmovntdq %%ymm1, %1\n"
		"vmovntdq %%ymm2, %2\n" "vmovntdq %%ymm3, %3\n" "vmovdqu %12, %%ymm0\n"
		"vmovdqu %13, %%ymm1\n" "vmovdqu %14, %%ymm2\n" "vmovdqu %15, %%ymm3\n"
		"vmovntdq %%ymm0, %4\n" "vmovntdq %%ymm1, %5\n" "vmovntdq %%ymm2, %6\n"
		"vmovntdq %%ymm3, %7" : "=m"(pd[0]), "=m"(pd[1]), "=m"(pd[2]),
		"=m"(pd[3]), "=m"(pd[4]), "=m"(pd[5]), "=m"(pd[6]), "=m"(pd[7])
		:"m"(ps[0]), "m"(ps[1]), "m"(ps[2]), "m"(ps[3]), "m"(ps[4]), "m"(ps[5]),
		"m"(ps[6]), "m"(ps[7]) : "ymm0", "ymm1", "ymm2", "ymm3", "memory");
	__asm__ ("vmovdqu %8, %%ymm0\n" "vmovdqu %9, %%ymm1\n"
		"vmovdqu %10, %%ymm2\n" "vmovdqu %11, %%ymm3\n" "vmovntdq %%ymm0, %0\n"
		"vmovntdq %%ymm1, %1\n" "vmovntdq %%ymm2, %2\n" "vmovntdq %%ymm3, %3\n"
		"vmovdqu %12, %%ymm0\n" "vmovdqu %13, %%ymm1\n" "vmovdqu %14, %%ymm2\n"
		"vmovdqu %15, %%ymm3\n" "vmovntdq %%ymm0, %4\n" "vmovntdq %%ymm1, %5\n"
		"vmovntdq %%ymm2, %6\n" "vmovntdq %%ymm3, %7":"=m"(pd[8]), "=m"(pd[9]),
		"=m"(pd[10]), "=m"(pd[11]), "=m"(pd[12]), "=m"(pd[13]), "=m"(pd[14]),
		"=m"(pd[15]) :"m"(ps[8]), "m"(ps[9]), "m"(ps[10]), "m"(ps[11]),
		"m"(ps[12]), "m"(ps[13]), "m"(ps[14]), "m"(ps[15])
		:"ymm0", "ymm1", "ymm2", "ymm3", "memory");
}

#else

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline void	ft__cpykernel_stream(void *restrict d,
	const void *restrict const s, size_t offset)
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

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	ft_memcpy_stream_tail(void *restrict dest,
	const void *restrict const src, size_t n)
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
		*((t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n)) =
			*((t_blk512r)ft_overlap(src, sizeof(t_vu512a), n));
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_512_streaming(void *restrict dest,
	const void *restrict const src, size_t n)
{
	t_t_f64_size	s;
	size_t			delta;
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
		ft__cpykernel_stream(d, sr, s.i);
		s.i += 8;
	}
	ft_fence();
	ft_memcpy_stream_tail(d + (s.i << 6), sr + (s.i << 6), n - (s.i << 6));
}
