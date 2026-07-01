/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_fuzz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline void	*ft__handle_alignment_alloc(t_tailor *t, t_size size,
	t_u8 alignment)
{
	void	*tmp;

	if (alignment == 1)
	{
		tmp = ft_arena_alloc(&t->arena, size + 1, 32);
		if (!tmp)
			return (nullptr);
		tmp = (t_u8 *)tmp + 1;
	}
	else
		tmp = ft_arena_alloc(&t->arena, size, alignment);
	return (tmp);
}

__attribute__((__nonnull__(1, 2, 3)))
t_result	ft_tailor_buffers(t_tailor *t,
	t_size *sizes, t_u8 *alignment, t_size n)
{
	t_size				i;
	void				*tmp;
	t_arena_checkpoint	c;

	i = 0;
	c = ft_arena_checkpoint(&t->arena);
	t->rand_buffers.mem = ft_arena_alloc(&t->arena, n * sizeof(t_buffer), 32);
	if (!t->rand_buffers.mem)
		return (ft_arena_rewind(&t->arena, c), KO);
	t->rand_buffers.size = n;
	while (i < n)
	{
		tmp = ft__handle_alignment_alloc(t, sizes[i], alignment[i]);
		if (!tmp)
			return (ft_arena_rewind(&t->arena, c), KO);
		((t_buffer *)t->rand_buffers.mem)[i] = ft_fatptr(tmp, sizes[i]);
		++i;
	}
	return (OK);
}
