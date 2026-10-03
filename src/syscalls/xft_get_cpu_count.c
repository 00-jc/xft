/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_cpu_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:03:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 13:06:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "syscalls.h"

__attribute__((pure, __nonnull__(1), unused, __always_inline__, __used__))
inline t_size	xft__cpu_count(t_size *__restrict__ const set)
{
	const t_size	size = 128 / sizeof(t_size);
	t_size			i;
	t_size			sum;

	i = 0;
	sum = 0;
	while (i < size)
		sum += xft_popcount_u64(set[i++]);
	return (sum);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_get_cpu_count(t_size *__restrict__ const count)
{
	t_size		set[128 / sizeof(t_size)];
	int			res;

	xft_bzero(set, sizeof(set));
	res = xft_sched_getaffinity(xft_getpid(), sizeof(set), set);
	if (__builtin_expect(res < 0, 0))
		return (KO);
	*count = xft__cpu_count(set);
	return (OK);
}
