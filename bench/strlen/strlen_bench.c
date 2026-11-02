/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_bench.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:33:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:33:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "cstr_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_strlen(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_strlen_test_varied, "xft_strlen_varied", "strlen_varied"},
	{xft_strlen_test_short_aligned, "xft_strlen_short_aligned",
		"strlen_short_aligned"},
	{xft_strlen_test_short_unaligned, "xft_strlen_short_unaligned",
		"strlen_short_unaligned"},
	{xft_strlen_test_medium_aligned, "xft_strlen_medium_aligned",
		"strlen_medium_aligned"},
	{xft_strlen_test_medium_unaligned, "xft_strlen_medium_unaligned",
		"strlen_medium_unaligned"},
	{xft_strlen_test_large_aligned, "xft_strlen_large_aligned",
		"strlen_large_aligned"},
	{xft_strlen_test_large_unaligned, "xft_strlen_large_unaligned",
		"strlen_large_unaligned"},
	};

	if (!xft_strlen_bench_buffers(t))
		xft_exit_process(1);
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
