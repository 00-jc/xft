/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_start_tls_for_main_thread.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 15:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>
#include <xft/mem.h>
#include <xft/xft_p_rt.h>
#include <xft/xft_p_syscalls.h>

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__, __nonnull__(1, 2)))
inline t_uptr	xft_tls_fill(t_u8 *__restrict__ const area,
	const t_sysinfo_linux *__restrict__ const l)
{
	const t_uptr	tp = (t_uptr)area + l->tls_tp_offset;

	xft_memcpy(area + l->tls_block_offset, l->tls_image, l->tls_filesz);
	*(t_uptr *)tp = tp;
	return (tp);
}

__attribute__((__flatten__))
t_result	xft_start_tls_for_main_thread(t_sysinfo sysinfo)
{
	static t_tls_page						page;
	const t_sysinfo_linux *__restrict__		l = &sysinfo._linux;
	t_u8									*area;

	area = page;
	if (__builtin_expect(l->tls_size + l->tls_align > sizeof(page), 0))
		area = xft_mmap(l->tls_size + l->tls_align, xft_prot_read
				| xft_prot_write, xft_map_private | xft_map_anonymous);
	if (__builtin_expect(xft_map_failed(area), 0))
		return (KO);
	area = xft_align_fwd(area, l->tls_align);
	return ((t_result)(xft_set_thread_pointer(xft_tls_fill(area, l)) == 0));
}

#elif defined(__linux__)

__attribute__((const))
t_result	xft_start_tls_for_main_thread(t_sysinfo sysinfo)
{
	(void)sysinfo;
	return (OK);
}

#endif
