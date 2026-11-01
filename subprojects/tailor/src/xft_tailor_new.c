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
static inline t_result	xft__tailor_alloc(t_tailor *t, t_sysinfo sysinfo)
{
	const t_thread_opts	opts = {.stack_size = XFT_THREAD_STACKSIZE,
		.cpu_pinning = true, .use_only_physical = true};

	t->gpa = xft_new_gpa();
	t->arena = xft_new_arena();
	if (t->gpa.slab == nullptr || t->arena.current == nullptr)
		return (xft_destroy_arena(&t->arena), xft_gpa_destroy(&t->gpa), KO);
	t->jobs = xft_new_vec(xft_gpa_allocator(&t->gpa), 32,
			sizeof(t_tailor_job));
	t->results = xft_new_vec(xft_gpa_allocator(&t->gpa), 32,
			sizeof(t_tailor_result));
	if (t->jobs.buf.mem == nullptr || t->results.buf.mem == nullptr
		|| !xft_threadpool_init(xft_gpa_allocator(&t->gpa), sysinfo, opts,
			&t->pool))
		return (xft_destroy_arena(&t->arena), xft_gpa_destroy(&t->gpa), KO);
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_new_tailor(t_tailor *t, t_sysinfo sysinfo, t_f64 warmup_sec,
	t_u64a min_samples)
{
	t_u64a		actualtime;

	if (__builtin_expect(!xft__tailor_alloc(t, sysinfo), 0))
		return (KO);
	actualtime = (t_u64a)(xft_dtern(warmup_sec < .75, .75, warmup_sec) * 1e9);
	t->phase1_ns = actualtime / 5;
	t->phase2_ns = actualtime - t->phase1_ns;
	t->rand_buffers = xft_fatptr(nullptr, 0);
	t->min_samples = xft_tern(min_samples < 150, 150, min_samples);
	t->writer = xft_get_fs_writer(xft_fatptr(t->buffer, TAILOR_BUFFER_SIZE),
			xft_get_stdout());
	return (OK);
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
