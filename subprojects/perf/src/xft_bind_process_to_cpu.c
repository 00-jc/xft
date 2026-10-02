/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_bind_process_to_cpu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 12:06:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perf.h"

t_result	xft_bind_process_to_cpu(t_u32 cpu)
{
	int			pid;
	t_size		mask[128 / sizeof(t_size)];

	pid = xft_getpid();
	xft_memset(mask, 0, sizeof(mask));
	mask[cpu >> 6] |= (t_u64a)1 << (cpu & 63);
	if (xft_sched_setaffinity(pid, sizeof(mask), mask) == -1)
		return (KO);
	return (OK);
}
