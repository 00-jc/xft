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
inline void	ft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{ft_vec_bench_push_back, (t_blk8r)"vec_push_back"},
	{ft_vec_bench_push_back_reserved, (t_blk8r)"vec_push_back_reserved"},
	{ft_vec_bench_push_pop, (t_blk8r)"vec_pop"},
	{ft_vec_bench_read, (t_blk8r)"vec_read"},
	{ft_vec_bench_extend, (t_blk8r)"vec_extend"},
	{ft_vec_bench_remove_front, (t_blk8r)"vec_remove_front"},
	};
	t_tailor				t;

	(void)sp;
	ft_bind_process_to_cpu(0);
	if (!ft_tailor_new(&t, 2, 2000))
		ft_exit(1);
	(void)ft_tailor_bench(&t, benches, 6);
	ft_gpa_destroy(ft_get_bench_vec_gpa());
	ft_tailor_destroy(&t);
	ft_exit(0);
}
