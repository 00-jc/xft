/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench.h"

__attribute__((__always_inline__, __used__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	t_tailor	t;

	((void)sp, xft_bind_process_to_cpu(0));
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	xft_stl_bench_vector(&t);
	xft_stl_bench_map(&t);
	xft_stl_bench_map_strings(&t);
	xft_stl_bench_map_strings_1m(&t);
	xft_gpa_destroy(xft_get_bench_vec_gpa());
	xft_gpa_destroy(xft_get_bench_swiss_gpa());
	(xft_tailor_destroy(&t), xft_exit(0));
}
