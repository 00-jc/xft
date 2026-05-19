/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_streaming.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:48:56 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 04:24:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if defined (__x86_64__) && FT_HAS_512_VEC

__attribute__((__nonnull__(1), __always_inline__, __hot__))
inline void	ft__setkernel_stream(void *restrict d,
	const t_u8 c, size_t offset)
{
	__asm__ (
		"vpbroadcastb %[byte], %%zmm0\n\t"
		"vmovntdq %%zmm0, %0\n\t"
		"vmovntdq %%zmm0, %1\n\t"
		"vmovntdq %%zmm0, %2\n\t"
		"vmovntdq %%zmm0, %3\n\t"
		"vmovntdq %%zmm0, %4\n\t"
		"vmovntdq %%zmm0, %5\n\t"
		"vmovntdq %%zmm0, %6\n\t"
		"vmovntdq %%zmm0, %7"
		: "=m"(((t_blk512wa)d)[offset + 0]),
		"=m"(((t_blk512wa)d)[offset + 1]),
		"=m"(((t_blk512wa)d)[offset + 2]),
		"=m"(((t_blk512wa)d)[offset + 3]),
		"=m"(((t_blk512wa)d)[offset + 4]),
		"=m"(((t_blk512wa)d)[offset + 5]),
		"=m"(((t_blk512wa)d)[offset + 6]),
		"=m"(((t_blk512wa)d)[offset + 7])
		: [byte] "r"((unsigned)c)
		: "zmm0", "memory"
		);
	__asm__("sfence" ::: "memory");
}

#elif defined (__x86_64__) && FT_HAS_256_VEC

__attribute__((__nonnull__(1), __always_inline__, __hot__))
inline void	ft__setkernel_stream(void *restrict d,
	const t_u8 c, size_t offset)
{
	t_blk256wa	p;

	p = (t_blk256wa)((t_u8 *)d + (offset << 6));
	__asm__ (
		"vpbroadcastb %[byte], %%ymm0\n\t"
		"vmovntdq %%ymm0, %0\n\t" "vmovntdq %%ymm0, %1\n\t"
		"vmovntdq %%ymm0, %2\n\t" "vmovntdq %%ymm0, %3\n\t"
		"vmovntdq %%ymm0, %4\n\t" "vmovntdq %%ymm0, %5\n\t"
		"vmovntdq %%ymm0, %6\n\t" "vmovntdq %%ymm0, %7\n\t"
		"vmovntdq %%ymm0, %8\n\t" "vmovntdq %%ymm0, %9\n\t"
		"vmovntdq %%ymm0, %10\n\t" "vmovntdq %%ymm0, %11\n\t"
		"vmovntdq %%ymm0, %12\n\t" "vmovntdq %%ymm0, %13\n\t"
		"vmovntdq %%ymm0, %14\n\t" "vmovntdq %%ymm0, %15"
		: "=m"(p[0]), "=m"(p[1]),
		"=m"(p[2]), "=m"(p[3]),
		"=m"(p[4]), "=m"(p[5]),
		"=m"(p[6]), "=m"(p[7]),
		"=m"(p[8]), "=m"(p[9]),
		"=m"(p[10]), "=m"(p[11]),
		"=m"(p[12]), "=m"(p[13]),
		"=m"(p[14]), "=m"(p[15])
		: [byte] "r"((unsigned)c)
		: "ymm0", "memory"
		);
}

#else

__attribute__((__nonnull__(1), __always_inline__, __hot__))
inline void	ft__setkernel_stream(void *restrict d,
	const t_u8 c, size_t offset)
{
	register t_vu512a	x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	((t_blk512wa)d)[offset + 0] = x;
	((t_blk512wa)d)[offset + 1] = x;
	((t_blk512wa)d)[offset + 2] = x;
	((t_blk512wa)d)[offset + 3] = x;
	((t_blk512wa)d)[offset + 4] = x;
	((t_blk512wa)d)[offset + 5] = x;
	((t_blk512wa)d)[offset + 6] = x;
	((t_blk512wa)d)[offset + 7] = x;
}

#endif

__attribute__((__always_inline__, __nonnull__(1)))
inline void	ft_memset_stream_tail(void *restrict dest,
	const t_u8 c, size_t n)
{
	register t_vu512a	x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
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
		*((t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n)) = x;
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_512_streaming(void *restrict dest,
	const t_u8 c, size_t n)
{
	t_t_f64_size			s;
	size_t					delta;
	t_u8					*d;
	register t_vu512a		x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = x;
	d = (t_u8 *)dest + delta;
	n -= delta;
	s.blks = (n >> 6);
	s.i = 0;
	while (s.i + 8 <= s.blks)
	{
		ft__setkernel_stream(d, c, s.i);
		s.i += 8;
	}
	ft_fence();
	ft_memset_stream_tail(d + (s.i << 6), c, n - (s.i << 6));
}
