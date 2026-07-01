/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_tailor_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_TAILOR_TYPES_H
# define FT_P_TAILOR_TYPES_H

# include "primitives.h"

typedef struct s_datapoint
{
	t_size		n;
	t_size		iters;
	t_size		bytes_processed;
	t_f64		mu;
	t_f64		m2;
	t_f64		min;
	t_f64		max;
}	t_datapoint;

typedef struct s_tailor_calib
{
	t_datapoint		dp;
	t_size			inner;
	t_u64a			cold;
}	t_tailor_calib;

typedef struct s_phase1
{
	t_u64a	sum;
	t_u64a	n;
	t_u64a	iters;
	t_u64a	cap;
}	t_phase1;

typedef struct s_plankb
{
	t_u64a		b;
	t_u64a		k;
	t_u64a		k_runs;
	t_datapoint	dp;
}	t_plankb;

#endif
