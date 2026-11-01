/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:14:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "vec_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_vec(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_vec_bench_push_back, "xft_vec_push_back", "vec_push_back"},
	{xft_vec_bench_push_back_reserved, "xft_vec_push_back_reserved",
		"vec_push_back_reserved"},
	{xft_vec_bench_push_pop, "xft_vec_push_pop", "vec_push_pop"},
	{xft_vec_bench_read, "xft_vec_read", "vec_read"},
	{xft_vec_bench_extend, "xft_vec_extend", "vec_extend"},
	{xft_vec_bench_remove_front, "xft_vec_remove_front", "vec_remove_front"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
