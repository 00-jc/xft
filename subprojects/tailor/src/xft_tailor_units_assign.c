/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_units_assign.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/indexmap.h>
#include <xft/cstr.h>

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline t_result	xft__units_intern(t_tailor *t, t_tailor_units *u,
	const char *group, t_size i)
{
	const t_buffer	key = xft_fatptr((const t_u8 *)group, xft_strlen(group));
	t_result		ret;

	u->uid[i] = xft_indexmap_lookup(&u->map, key);
	ret = (t_result){.ok = OK};
	if (u->uid[i] == INDEXMAP_NPOS)
		ret = xft_indexmap_insert(xft_arena_allocator(&t->arena),
				&u->map, key, u->n);
	return (ret);
}

__attribute__((__nonnull__(1, 2, 3)))
t_result	xft__units_assign(t_tailor *t, t_tailor_units *u,
	const t_tailor_job *jobs, t_size size)
{
	t_size		i;
	t_result	ret;

	i = 0;
	while (i < size)
	{
		u->uid[i] = u->n;
		ret = (t_result){.ok = OK};
		if (jobs[i].result.group != nullptr)
			ret = xft__units_intern(t, u, jobs[i].result.group, i);
		if (!ret.ok)
			return (ret);
		if (u->uid[i] == INDEXMAP_NPOS || u->uid[i] == u->n)
			u->uid[i] = u->n++;
		u->units[u->uid[i]].n++;
		++i;
	}
	return ((t_result){.ok = OK});
}
