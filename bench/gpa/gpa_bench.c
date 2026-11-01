/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "alloc_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_gpa(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_gpa_bench_8, "gpa_alloc_free_8", nullptr},
	{xft_gpa_bench_64, "gpa_alloc_free_64", nullptr},
	{xft_gpa_bench_512, "gpa_alloc_free_512", nullptr},
	{xft_gpa_bench_8k, "gpa_alloc_free_8k", nullptr},
	{xft_gpa_bench_varied, "gpa_alloc_free_varied", nullptr},
	{xft_gpa_bench_random, "gpa_alloc_free_random", nullptr},
	{xft_gpa_bulk_bench_64, "gpa_bulk_64", nullptr},
	{xft_gpa_bulk_bench_512, "gpa_bulk_512", nullptr},
	{xft_gpa_bulk_bench_mixed, "gpa_bulk_mixed", nullptr},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
