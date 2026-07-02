/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_calibration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:07:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"
#include "math.h"
#include <float.h>

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_u64	ft_tailor_run1(t_tailor_fn fn, t_tailor_arg *arg)
{
	t_u64		t0;
	t_u64		t1;

	t0 = ft_get_nanos();
	fn(arg);
	t1 = ft_get_nanos();
	return (ft_tern(t1 - t0 == 0, 1, t1 - t0));
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_phase1	ft_tailor_calibrate_mu(t_tailor *t, t_tailor_fn fn)
{
	t_u64a			sum;
	t_u64a			total;
	t_u64			deadline;
	t_u64			cap;
	t_tailor_arg	arg;

	arg.iters = 1;
	arg.buffers = t->rand_buffers;
	ft_xoshiro_init(arg.xoshiro);
	ft_tailor_run1(fn, &arg);
	arg.iters = 2;
	sum = ft_tailor_run1(fn, &arg);
	arg.iters = 1;
	cap = ft_tern(sum > 200, (1 << 20), TAILOR_MAX);
	deadline = ft_get_nanos() + t->phase1_ns;
	sum = 0;
	total = 0;
	while (__builtin_expect(ft_get_nanos() < deadline, 1))
	{
		sum += ft_tailor_run1(fn, &arg);
		total += arg.iters;
		arg.iters = ft_tern(arg.iters < cap, arg.iters << 1, cap);
	}
	return ((t_phase1){.sum = sum, .n = total, .iters = arg.iters, .cap = cap});
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_f64	ft__welford(t_datapoint *dp, t_u64a sample, t_u64a n)
{
	t_f64	x;
	t_f64	d1;
	t_f64	d2;
	t_f64	s;
	t_f64	ci;

	++dp->n;
	x = (t_f64)sample / (t_f64)n;
	d1 = x - dp->mu;
	dp->mu += d1 / (t_f64)dp->n;
	d2 = x - dp->mu;
	dp->m2 += d1 * d2;
	dp->min = ft_dtern(x < dp->min, x, dp->min);
	dp->max = ft_dtern(dp->max < x, x, dp->max);
	ci = 1000.0;
	if ((dp->n & 15) == 0)
	{
		s = (dp->m2 / (t_f64)(dp->n - 1)) / (t_f64)dp->n;
		ci = 1.96 * ft_dsqrt(s) / dp->mu;
	}
	return (ft_dtern(ci < 0.01, ci, 1000.0));
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_datapoint	ft_tailor_calibrate_welford(t_tailor *t,
	t_tailor_fn fn)
{
	t_datapoint		dp;
	t_phase1		p1;
	t_u64a			deadline;
	t_f64			fpv[3];
	t_tailor_arg	arg;

	dp = (t_datapoint){0, 0, 0, 0, 0, DBL_MAX, 0};
	p1 = ft_tailor_calibrate_mu(t, fn);
	ft_xoshiro_init(arg.xoshiro);
	arg.buffers = t->rand_buffers;
	fpv[0] = (t_f64)p1.sum / (t_f64)p1.n;
	fpv[1] = (t_f64)t->phase2_ns / (t_f64)(t->min_samples << 1);
	fpv[2] = 50000.0 / fpv[0];
	fpv[0] = fpv[1] / fpv[0];
	arg.iters = (t_size)ft_dtern(fpv[0] < fpv[2], fpv[0], fpv[2]);
	arg.iters = ft_tern(arg.iters == 0, 1, arg.iters);
	arg.iters = ft_tern(arg.iters > TAILOR_MAX, TAILOR_MAX, arg.iters);
	ft_tailor_run1(fn, &arg);
	fpv[0] = 100.0;
	deadline = ft_get_nanos() + t->phase2_ns;
	while (__builtin_expect((ft_get_nanos() < deadline && !(0 <= fpv[0]
					&& fpv[0] < 0.01)) || dp.n < t->min_samples, 1))
		fpv[0] = ft__welford(&dp, ft_tailor_run1(fn, &arg), arg.iters);
	dp.iters = arg.iters;
	return (dp);
}

__attribute__((__nonnull__(1, 2)))
t_plankb	ft_get_kb(t_tailor *t, t_tailor_fn fn)
{
	t_datapoint		dp;
	t_u64			div;
	t_f64			cv;
	t_f64			ktmp;
	t_u64a			kb[2];

	dp = ft_tailor_calibrate_welford(t, fn);
	cv = ft_dsqrt(dp.m2 / (t_f64)(dp.n - 1)) / dp.mu;
	ktmp = 1.96 * (cv / K_REL_CI);
	ktmp = 1.5 * ktmp * ktmp;
	div = (t_u64a)dp.mu * dp.iters;
	div = ft_tern(div == 0, 1, div);
	kb[0] = ((t->phase1_ns + t->phase2_ns) << 2) / div;
	kb[1] = (t_u64a)ktmp;
	kb[1] = ft_tern(kb[1] < 120, 120, kb[1]);
	kb[1] = ft_tern(10000 < kb[1], 10000, kb[1]);
	kb[1] = ft_tern(kb[0] < kb[1], kb[0], kb[1]);
	kb[0] = ft_tern(cv < 0.1, 2000, 10000);
	return ((t_plankb){.b = kb[0],
		.k_runs = (kb[1] + K_WARMUP + (kb[1] / 10)), .k = kb[1],
		.dp = dp});
}
