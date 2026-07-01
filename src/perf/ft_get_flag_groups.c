/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flag_groups.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_perf.h"

__attribute__((__always_inline__, const))
inline const t_hw_counters	*get_hw_counters(void)
{
	static const t_hw_counters	counters[] = {
		CYCLES, INSTR, CACHEHITLL, CACHEMISS,
		BRANCH, BRANCHMISS,
	};

	return (counters);
}

__attribute__((__always_inline__, const))
inline const t_sw_counters	*get_sw_counters(void)
{
	static const t_sw_counters	counters[] = {
		DUMMY, ALIGNMENT, PAGEFAULT
	};

	return (counters);
}
