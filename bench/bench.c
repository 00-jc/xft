/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:44:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include <xft/rt.h>
#include "bench.h"

static void	bench_queue(t_tailor *t)
{
	xft_bench_memcpy(t);
	xft_bench_memcpy_stream(t);
	xft_bench_memmove(t);
	xft_bench_memset(t);
	xft_bench_memset_stream(t);
	xft_bench_strlen(t);
	xft_bench_gpa(t);
	xft_bench_arena(t);
	xft_bench_vec(t);
	xft_bench_soa(t);
	xft_bench_swissmap(t);
	xft_bench_indexmap(t);
	xft_libc_bench_memcpy(t);
	xft_libc_bench_strlen(t);
	xft_stl_bench_vector(t);
	xft_stl_bench_map_strings(t);
	xft_stl_bench_map_strings_1m(t);
}

__attribute__((__always_inline__, __used__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	t_tailor	t;

	if (!xft_new_tailor(&t, xft_get_sysinfo(sp), 2, 2000))
		xft_exit_process(1);
	bench_queue(&t);
	if (!xft_tailor_run(&t))
		xft_exit_process(1);
	xft_tailor_report(&t);
	if (!xft_tailor_compare(&t))
		xft_exit_process(1);
	(xft_tailor_destroy(&t), xft_exit_process(0));
}
