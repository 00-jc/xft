/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_bench_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:34:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:34:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "bench.h"
#include "libc_bench.h"
#include <xft/rt.h>

static void	libc_memcpy_queue(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_libc_memcpy_varied, "libc_memcpy_varied", "memcpy_varied"},
	{xft_libc_memcpy_short_aligned, "libc_memcpy_short_aligned",
		"memcpy_short_aligned"},
	{xft_libc_memcpy_short_unaligned, "libc_memcpy_short_unaligned",
		"memcpy_short_unaligned"},
	{xft_libc_memcpy_medium_aligned, "libc_memcpy_medium_aligned",
		"memcpy_medium_aligned"},
	{xft_libc_memcpy_medium_unaligned, "libc_memcpy_medium_unaligned",
		"memcpy_medium_unaligned"},
	{xft_libc_memcpy_large_aligned, "libc_memcpy_large_aligned",
		"memcpy_large_aligned"},
	{xft_libc_memcpy_large_unaligned, "libc_memcpy_large_unaligned",
		"memcpy_large_unaligned"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}

void	xft_libc_bench_memcpy(t_tailor *t)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};

	if (!xft_tailor_buffers(t, bufsizes, bufalign, 28))
		xft_exit_process(1);
	libc_memcpy_queue(t);
}

void	xft_libc_bench_strlen(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_libc_strlen_varied, "libc_strlen_varied", "strlen_varied"},
	{xft_libc_strlen_short_aligned, "libc_strlen_short_aligned",
		"strlen_short_aligned"},
	{xft_libc_strlen_short_unaligned, "libc_strlen_short_unaligned",
		"strlen_short_unaligned"},
	{xft_libc_strlen_medium_aligned, "libc_strlen_medium_aligned",
		"strlen_medium_aligned"},
	{xft_libc_strlen_medium_unaligned, "libc_strlen_medium_unaligned",
		"strlen_medium_unaligned"},
	{xft_libc_strlen_large_aligned, "libc_strlen_large_aligned",
		"strlen_large_aligned"},
	{xft_libc_strlen_large_unaligned, "libc_strlen_large_unaligned",
		"strlen_large_unaligned"},
	};

	if (!xft_strlen_bench_buffers(t))
		xft_exit_process(1);
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
