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

#include <xft/tailor.h>
#include "soa_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_soa(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_soa_bench_append, "soa_append", nullptr},
	{xft_soa_bench_append_reserved, "soa_append_reserved", nullptr},
	{xft_soa_bench_append_unchecked, "soa_append_unchecked", nullptr},
	{xft_soa_bench_update, "soa_update", nullptr},
	{xft_soa_bench_aos_update, "aos_update", nullptr},
	{xft_soa_bench_read, "soa_read", nullptr},
	{xft_soa_bench_column_sum, "soa_column_sum", nullptr},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
