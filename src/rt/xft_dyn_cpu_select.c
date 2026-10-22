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

__attribute__((const, __always_inline__, __flatten__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	unsigned int		x[4];
	t_xft_arch			v;
	unsigned long long	xcr0;

	v = (t_xft_arch){0};
	if (__builtin_expect(!__get_cpuid(1, &x[0], &x[1], &x[2], &x[3]), 0))
		return (v);
	v.has_128_vec = (x[3] >> 26) & 1;
	if (!((x[2] >> 27) & 1) || !((x[2] >> 28) & 1))
		return (v);
	xcr0 = xft_xgetbv0();
	if (__builtin_expect((xcr0 & 0x06) != 0x06
			|| !__get_cpuid_count(7, 0, &x[0], &x[1],
				&x[2], &x[3]), 0))
		return (v);
	v.has_256_vec = (x[1] >> 5) & 1;
	if ((xcr0 & 0xE0) != 0xE0)
		return (v);
	v.has_512_vec = ((x[1] >> 16) & 1)
		&& ((x[1] >> 17) & 1)
		&& ((x[1] >> 30) & 1)
		&& ((x[1] >> 31) & 1)
		&& ((x[2] >> 6) & 1);
	return (v);
}

#elif defined(__aarch64__)

__attribute__((const, __always_inline__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	return ((t_xft_arch){.has_128_vec = true,
		.has_256_vec = 0,
		.has_512_vec = 0,
	});
}

#else

__attribute__((const, __always_inline__))
inline t_xft_arch	xft_dyn_cpu_select(void)
{
	return ((t_xft_arch){0});
}

#endif
