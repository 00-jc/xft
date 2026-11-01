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

#include <xft/tailor.h>
#include "indexmap_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_indexmap(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_imap_bench_insert_grow, "imap_insert_grow", nullptr},
	{xft_imap_bench_insert_reserved, "imap_insert_reserved", nullptr},
	{xft_imap_bench_lookup_hit, "imap_lookup_hit", nullptr},
	{xft_imap_bench_lookup_miss, "imap_lookup_miss", nullptr},
	{xft_imap_bench_delete_insert, "imap_delete_insert", nullptr},
	{xft_imap_bench_large_lookup_hit, "imap_1m_lookup_hit", nullptr},
	{xft_imap_bench_large_lookup_miss, "imap_1m_lookup_miss", nullptr},
	{xft_imap_bench_large_delete_insert, "imap_1m_delete_insert", nullptr},
	};

	(void)xft_get_bench_imap_keys();
	(void)xft_get_bench_imap_large_keys();
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
