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

#include <xft/tailor.h>
#include "swissmap_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_swissmap(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_bench_insert_grow, "swiss_insert_grow", nullptr},
	{xft_swiss_bench_insert_reserved, "swiss_insert_reserved", nullptr},
	{xft_swiss_bench_lookup_hit, "swiss_lookup_hit", nullptr},
	{xft_swiss_bench_lookup_miss, "swiss_lookup_miss", nullptr},
	{xft_swiss_bench_delete_insert, "swiss_delete_insert", nullptr},
	{xft_swiss_bench_large_lookup_hit, "swiss_1m_lookup_hit", nullptr},
	{xft_swiss_bench_large_lookup_miss, "swiss_1m_lookup_miss", nullptr},
	{xft_swiss_bench_large_delete_insert, "swiss_1m_delete_insert", nullptr},
	};

	(void)xft_get_bench_swiss_keys();
	(void)xft_get_bench_swiss_large_keys();
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
