/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bind_process_to_cpu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:17:04 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/17 20:52:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perf.h"

t_result	ft_bind_process_to_cpu(t_u32 cpu)
{
	pid_t		pid;
	cpu_set_t	set;

	pid = getpid();
	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	if (sched_setaffinity(pid, sizeof(set), &set) == -1)
		return (KO);
	return (OK);
}
