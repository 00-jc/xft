/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:54:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:03:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/os.h>

__attribute__((__nonnull__(3), __flatten__))
t_result	xft_threadpool_init(t_allocator allocator,
	const t_sysinfo info, t_threadpool *__restrict__ const tp)
{
	t_size			cpu_count;

	if (__builtin_expect(xft_get_cpu_count(&cpu_count) == KO, 0))
		return (KO);
	tp->global_lock = xft_unlocked;
	tp->n_workers = cpu_count;
	tp->wake_up = 0;
	tp->shut_down = 0;
	tp->global_q_head = nullptr;
	tp->global_q_tail = nullptr;
	tp->n_maybe_parked = 0;
	tp->q_len = 0;
	if (__builtin_expect(xft__init_rings(allocator, tp) == KO, 0))
		return (KO);
	if (__builtin_expect(xft__init_threads(allocator, info, tp) == KO, 0))
		return ((void)(xft__free_rings(allocator, tp, tp->n_workers)), KO);
	return (OK);
}
