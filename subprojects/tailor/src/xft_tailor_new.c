/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 15:03:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/io.h>
#include <xft/vec.h>

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_containers(t_tailor *t, t_sysinfo sysinfo)
{
	const t_thread_opts	opts = {.stack_size = XFT_THREAD_STACKSIZE,
		.cpu_pinning = true, .use_only_physical = true};
	t_result			ret;

	ret = xft_new_vec(xft_gpa_allocator(&t->gpa), &t->jobs, 32,
			sizeof(t_tailor_job));
	if (!ret.ok)
		return (ret);
	ret = xft_new_vec(xft_gpa_allocator(&t->gpa), &t->results, 32,
			sizeof(t_tailor_result));
	if (!ret.ok)
		return (ret);
	return (xft_threadpool_init(xft_gpa_allocator(&t->gpa), sysinfo, opts,
			&t->pool));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_alloc(t_tailor *t, t_sysinfo sysinfo)
{
	t_result	ret;

	ret = xft_new_gpa(&t->gpa);
	if (!ret.ok)
		return (ret);
	ret = xft_new_arena(&t->arena);
	if (!ret.ok)
		return (xft_gpa_destroy(&t->gpa), ret);
	ret = xft__tailor_containers(t, sysinfo);
	if (!ret.ok)
		return (xft_destroy_arena(&t->arena), xft_gpa_destroy(&t->gpa), ret);
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1)))
t_result	xft_new_tailor(t_tailor *t, t_sysinfo sysinfo, t_f64 warmup_sec,
	t_u64a min_samples)
{
	t_u64a		actualtime;
	t_result	ret;

	ret = xft__tailor_alloc(t, sysinfo);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	actualtime = (t_u64a)(xft_dtern(warmup_sec < .75, .75, warmup_sec) * 1e9);
	t->phase1_ns = actualtime / 5;
	t->phase2_ns = actualtime - t->phase1_ns;
	t->rand_buffers = xft_fatptr(nullptr, 0);
	t->min_samples = xft_tern(min_samples < 150, 150, min_samples);
	t->writer = xft_fs_writer(&t->writer_fs, xft_get_stdout(),
			xft_fatptr(t->buffer, TAILOR_BUFFER_SIZE));
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1)))
void	xft_tailor_destroy(t_tailor *t)
{
	xft_threadpool_destroy(xft_gpa_allocator(&t->gpa), &t->pool);
	xft_vec_destroy(xft_gpa_allocator(&t->gpa), &t->jobs);
	xft_vec_destroy(xft_gpa_allocator(&t->gpa), &t->results);
	xft_destroy_arena(&t->arena);
	xft_gpa_destroy(&t->gpa);
}
