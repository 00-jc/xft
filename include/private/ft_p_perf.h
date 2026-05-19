/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_perf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:23:23 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/18 20:36:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_PERF_H
# define FT_P_PERF_H

# include "perf.h"

typedef struct s_perf_read
{
	t_u64	nr;
	t_u64	enabled;
	t_u64	running;
	t_u64	val[9];
}	t_perf_read;

const t_hw_counters		*get_hw_counters(void)\
							__attribute__((const));

const t_sw_counters		*get_sw_counters(void)\
							__attribute__((const));

#endif
