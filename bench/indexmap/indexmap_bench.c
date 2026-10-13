/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexmap_bench.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "indexmap_bench.h"
#include "rt.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_imap_bench_insert_grow, (t_blk8r)"imap_insert_grow"},
	{xft_imap_bench_insert_reserved, (t_blk8r)"imap_insert_reserved"},
	{xft_imap_bench_lookup_hit, (t_blk8r)"imap_lookup_hit"},
	{xft_imap_bench_lookup_miss, (t_blk8r)"imap_lookup_miss"},
	{xft_imap_bench_delete_insert, (t_blk8r)"imap_delete_insert"},
	{xft_imap_bench_large_lookup_hit, (t_blk8r)"imap_1m_lookup_hit"},
	{xft_imap_bench_large_lookup_miss, (t_blk8r)"imap_1m_lookup_miss"},
	{xft_imap_bench_large_delete_insert, (t_blk8r)"imap_1m_delete_insert"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 8);
	xft_gpa_destroy(xft_get_bench_imap_gpa());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
