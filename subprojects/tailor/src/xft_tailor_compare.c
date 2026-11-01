/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_compare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/indexmap.h>
#include <xft/macros.h>
#include <xft/fmt.h>
#include <xft/math.h>
#include <xft/vec.h>

#define C0		" ≈ %s\n"
#define C1		" ├─ %s = %f cycles per_call (baseline) [%f ns]\n"
#define C2		" ├─ %s = %f cycles per_call (%fx faster) [%f ns]\n"
#define C3		" ├─ %s = %f cycles per_call (%fx slower) [%f ns]\n"

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_result	xft__tailor_link(t_tailor *t, t_tailor_groups *g,
	const t_tailor_result *r, t_size i)
{
	const t_buffer	key = xft_fatptr((const t_u8 *)r->group,
			xft_strlen(r->group));
	t_size			gid;

	gid = xft_indexmap_lookup(&g->map, key);
	if (gid == INDEXMAP_NPOS)
	{
		gid = g->count++;
		if (!xft_indexmap_insert(xft_arena_allocator(&t->arena), &g->map,
				key, gid))
			return (KO);
		g->head[gid] = i;
	}
	else
		g->next[g->tail[gid]] = i;
	g->tail[gid] = i;
	g->next[i] = INDEXMAP_NPOS;
	return (OK);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_result	xft__tailor_groups(t_tailor *t, t_tailor_groups *g,
	t_size n)
{
	const t_tailor_result	*r;
	t_size					i;

	g->count = 0;
	g->next = xft_arena_alloc(&t->arena, sizeof(t_size) * n * 3, 64);
	if (__builtin_expect(g->next == nullptr, 0))
		return (KO);
	g->head = g->next + n;
	g->tail = g->head + n;
	g->map = xft_new_indexmap_with(xft_arena_allocator(&t->arena), n);
	if (__builtin_expect(g->map.soa.ptr == nullptr, 0))
		return (KO);
	i = 0;
	while (i < n)
	{
		r = xft_vec_get(&t->results, i, sizeof(t_tailor_result));
		if (r->group != nullptr && !xft__tailor_link(t, g, r, i))
			return (KO);
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline void	xft__tailor_print_member(t_tailor *t,
	const t_tailor_result *base, const t_tailor_result *r)
{
	t_u64a	args[5];

	args[0] = (t_u64a)(t_uptr)r->name;
	args[1] = xft_strlen(r->name);
	args[2] = (t_dp){.f = r->cycles}.i;
	args[3] = (t_dp){.f = r->ns}.i;
	args[4] = args[3];
	args[3] = (t_dp){.f = xft_dtern(r->cycles < base->cycles,
			base->cycles / r->cycles, r->cycles / base->cycles)}.i;
	if (r == base)
		xft_fmt_writer(&t->writer, xft_fatptr((t_u8 *)C1, sizeof(C1) - 1),
			(t_u64a []){args[0], args[1], args[2], args[4]});
	else if (r->cycles < base->cycles)
		xft_fmt_writer(&t->writer, xft_fatptr((t_u8 *)C2, sizeof(C2) - 1),
			args);
	else
		xft_fmt_writer(&t->writer, xft_fatptr((t_u8 *)C3, sizeof(C3) - 1),
			args);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft__tailor_print_group(t_tailor *t,
	const t_tailor_groups *g, t_size gid)
{
	const t_tailor_result	*base = xft_vec_get(&t->results, g->head[gid],
			sizeof(t_tailor_result));
	t_size					i;
	t_u64a					args[2];

	args[0] = (t_u64a)(t_uptr)base->group;
	args[1] = xft_strlen(base->group);
	xft_fmt_writer(&t->writer, xft_fatptr((t_u8 *)ANSI_BCYAN C0 ANSI_RESET,
			sizeof(ANSI_BCYAN C0 ANSI_RESET) - 1), args);
	i = g->head[gid];
	while (i != INDEXMAP_NPOS)
	{
		xft__tailor_print_member(t, base,
			xft_vec_get(&t->results, i, sizeof(t_tailor_result)));
		i = g->next[i];
	}
	xft_writer_write(&t->writer, xft_fatptr((t_u8 *)"\n", 1));
}

__attribute__((__nonnull__(1)))
t_result	xft_tailor_compare(t_tailor *t)
{
	const t_arena_checkpoint	c = xft_arena_checkpoint(&t->arena);
	const t_size				n = xft_vec_len(&t->results,
			sizeof(t_tailor_result));
	t_tailor_groups				g;
	t_size						gid;

	if (n == 0)
		return (OK);
	if (__builtin_expect(!xft__tailor_groups(t, &g, n), 0))
		return (xft_arena_rewind(&t->arena, c), KO);
	gid = 0;
	while (gid < g.count)
		xft__tailor_print_group(t, &g, gid++);
	xft_arena_rewind(&t->arena, c);
	xft_writer_flush(&t->writer);
	return (OK);
}
