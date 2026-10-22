/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_bench.c                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "swissmap_bench.h"
#include "rt.h"

__attribute__((__always_inline__, __used__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_bench_insert_grow, (t_blk8r)"swiss_insert_grow"},
	{xft_swiss_bench_insert_reserved, (t_blk8r)"swiss_insert_reserved"},
	{xft_swiss_bench_lookup_hit, (t_blk8r)"swiss_lookup_hit"},
	{xft_swiss_bench_lookup_miss, (t_blk8r)"swiss_lookup_miss"},
	{xft_swiss_bench_delete_insert, (t_blk8r)"swiss_delete_insert"},
	{xft_swiss_bench_large_lookup_hit, (t_blk8r)"swiss_1m_lookup_hit"},
	{xft_swiss_bench_large_lookup_miss, (t_blk8r)"swiss_1m_lookup_miss"},
	{xft_swiss_bench_large_delete_insert, (t_blk8r)"swiss_1m_delete_insert"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 8);
	xft_gpa_destroy(xft_get_bench_swiss_gpa());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
