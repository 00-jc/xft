/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bind_process_to_cpu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perf.h"

t_result	ft_bind_process_to_cpu(t_u32 cpu)
{
	int		pid;
	t_u64a	mask[FT_CPU_SETSIZE >> 6];

	pid = ft_getpid();
	ft_memset(mask, 0, sizeof(mask));
	mask[cpu >> 6] |= (t_u64a)1 << (cpu & 63);
	if (ft_sched_setaffinity(pid, sizeof(mask), mask) == -1)
		return (KO);
	return (OK);
}
