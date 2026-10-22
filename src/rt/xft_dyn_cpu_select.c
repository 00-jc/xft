/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_dyn_cpu_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 01:58:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 02:38:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(__x86_64__) || defined(__i386__)

# include <cpuid.h>

__attribute__((const, __always_inline__))
static inline unsigned long long	xft_xgetbv0(void)
{
	unsigned int	lo;
	unsigned int	hi;

	__asm__ volatile ("xgetbv" : "=a"(lo), "=d"(hi) : "c"(0));
	return (((unsigned long long)hi << 32) | lo);
}

/*
 *	x86-64 psABI levels, each one on top of the previous:
 *	v1: SSE2.
 *	v2: leaf 1 ecx SSE3, SSSE3, CX16, SSE4.1, SSE4.2, POPCNT (0x00982201)
 *		and 0x80000001 ecx LAHF-SAHF (0x01).
 *	v3: leaf 1 ecx FMA, MOVBE, OSXSAVE, AVX, F16C (0x38401000),
 *		0x80000001 ecx LZCNT (0x20), leaf 7 ebx BMI1, AVX2, BMI2 (0x128)
 *		and the SSE and AVX state in XCR0 (0x06).
 *	v4: leaf 7 ebx AVX512F, DQ, CD, BW, VL (0xD0030000)
 *		and the opmask and ZMM state in XCR0 (0xE0).
 */

__attribute__((const, __always_inline__))
static inline t_x86_ver	xft_x86_ver(void)
{
	unsigned int	l1[4];
	unsigned int	l7[4];
	unsigned int	ex[4];

	if (__builtin_expect(!__get_cpuid(1, &l1[0], &l1[1], &l1[2], &l1[3]), 0))
		return (XFT_X86_NONE);
	if (!((l1[3] >> 26) & 1))
		return (XFT_X86_NONE);
	if (!__get_cpuid(0x80000001, &ex[0], &ex[1], &ex[2], &ex[3])
		|| (l1[2] & 0x00982201) != 0x00982201 || !(ex[2] & 0x01))
		return (XFT_X86_V1);
	if ((l1[2] & 0x38401000) != 0x38401000 || !(ex[2] & 0x20)
		|| (xft_xgetbv0() & 0x06) != 0x06
		|| !__get_cpuid_count(7, 0, &l7[0], &l7[1], &l7[2], &l7[3])
		|| (l7[1] & 0x128) != 0x128)
		return (XFT_X86_V2);
	if ((xft_xgetbv0() & 0xE0) != 0xE0 || (l7[1] & 0xD0030000) != 0xD0030000)
		return (XFT_X86_V3);
	return (XFT_X86_V4);
}

__attribute__((const, __always_inline__, __flatten__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	t_xft_arch	v;

	v.x86_64_ver = xft_x86_ver();
	v.has_128_vec = v.x86_64_ver >= XFT_X86_V1;
	v.has_256_vec = v.x86_64_ver >= XFT_X86_V3;
	v.has_512_vec = v.x86_64_ver >= XFT_X86_V4;
	return (v);
}

#elif defined(__aarch64__)

__attribute__((const, __always_inline__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	return ((t_xft_arch){.has_128_vec = true,
		.has_256_vec = 0,
		.has_512_vec = 0,
		.x86_64_ver = XFT_X86_NONE,
	});
}

#else

__attribute__((const, __always_inline__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	return ((t_xft_arch){0});
}

#endif
