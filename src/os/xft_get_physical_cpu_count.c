/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_physical_cpu_count.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:53:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/os.h>

__attribute__((__nonnull__(1)))
t_result	xft_get_physical_cpu_count(t_size *count)
{
	t_size	cpus;

	if (__builtin_expect(xft_get_cpu_count(&cpus) == KO, 0))
		return (KO);
	*count = xft_tern_s(cpus >> 1 != 0, cpus >> 1, cpus);
	return (OK);
}
