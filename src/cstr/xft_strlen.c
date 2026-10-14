/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_strlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 13:57:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_asm.h"
#include "cstr.h"

#define ALIGN 0xFFFULL
#define SIZE 0x1000ULL

__attribute__((pure, __nonnull__(1), __no_sanitize_address__,
	__always_inline__))
inline t_size	xft_strlen(const char *__restrict__ const str)
{
	t_uptr						a;
	t_nmask						w;
	t_nmask						m;
	t_u32a						offst;
	const t_nvec	*restrict	wp;

	wp = (t_blknr)(str);
	a = (t_uptr)str;
	offst = (t_uptr)wp & ALIGN;
	m = (t_nmask)(~0ULL >> (64 - xft_tern(offst + sizeof(t_nvec) > SIZE,
					SIZE - offst, 64)));
	w = xft_vmask(xft_vmask_load(wp, m) == 0) & m;
	if (__builtin_expect(w != 0, 1))
		return (((t_uptr)wp + xft_memctz_u64(w)) - a);
	wp = (t_blknr)((a & ~(sizeof(t_nvec) - 1)) + sizeof(t_nvec));
	while (1)
	{
		w = xft_vmask(*(t_blknra)wp == 0);
		if (__builtin_expect(w != 0, 1))
			return (((t_uptr)wp + xft_memctz_u64(w)) - a);
		++wp;
	}
}
