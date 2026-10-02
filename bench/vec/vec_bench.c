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

#include "tailor.h"
#include "vec_bench.h"
#include "rt.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_vec_bench_push_back, (t_blk8r)"vec_push_back"},
	{xft_vec_bench_push_back_reserved, (t_blk8r)"vec_push_back_reserved"},
	{xft_vec_bench_push_pop, (t_blk8r)"vec_pop"},
	{xft_vec_bench_read, (t_blk8r)"vec_read"},
	{xft_vec_bench_extend, (t_blk8r)"vec_extend"},
	{xft_vec_bench_remove_front, (t_blk8r)"vec_remove_front"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_tailor_new(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 6);
	xft_gpa_destroy(xft_get_bench_vec_gpa());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
