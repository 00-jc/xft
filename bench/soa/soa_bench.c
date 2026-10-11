/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "soa_bench.h"
#include "rt.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_soa_bench_append, (t_blk8r)"soa_append"},
	{xft_soa_bench_append_reserved, (t_blk8r)"soa_append_reserved"},
	{xft_soa_bench_append_unchecked, (t_blk8r)"soa_append_unchecked"},
	{xft_soa_bench_update, (t_blk8r)"soa_update"},
	{xft_soa_bench_aos_update, (t_blk8r)"aos_update"},
	{xft_soa_bench_read, (t_blk8r)"soa_read"},
	{xft_soa_bench_column_sum, (t_blk8r)"soa_column_sum"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 7);
	xft_gpa_destroy(xft_get_bench_soa_gpa());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
