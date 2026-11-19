/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_queue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/vec.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft_tailor_bench(t_tailor *t, t_tailor_bench benches[], t_size size)
{
	t_tailor_job	job;
	t_size			i;
	t_result		ret;

	i = 0;
	while (i < size)
	{
		job = (t_tailor_job){.t = t, .fn = benches[i].fn, .status = {.ok = KO},
			.buffers = t->rand_buffers,
			.result = {.name = benches[i].name, .group = benches[i].group}};
		ret = xft_vec_push_back(xft_gpa_allocator(&t->gpa), &t->jobs,
				(const t_u8 *)&job, sizeof(job));
		if (__builtin_expect(!ret.ok, 0))
			return (ret);
		++i;
	}
	return ((t_result){.ok = OK});
}
