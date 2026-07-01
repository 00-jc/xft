/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_tailor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:51:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_TAILOR_H
# define FT_P_TAILOR_H

# include "tailor.h"
# include "sort.h"

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

# ifndef TAILOR_MAX
#  define TAILOR_MAX 8388608
# endif

# define K_REL_CI 0.01
# define K_WARMUP 3

t_plankb		ft_get_kb(t_tailor *t, t_tailor_fn fn)\
					__attribute__((__nonnull__(1, 2)));

t_result		ft_bootstrap(t_tailor *t, t_buffer surv, t_plankb plan,\
					t_blk8r name) __attribute__((__nonnull__(1)));

void			ft_print_summary(t_buffer surv, t_plankb plan,\
					t_tailor_report_ctx ctx,\
					t_u64a data[4])\
					__attribute__((__nonnull__(4)));

t_result		ft_tailor_benchfn(t_tailor *t, t_tailor_fn fn, t_blk8r name)\
					__attribute__((__nonnull__(1)));

#endif
