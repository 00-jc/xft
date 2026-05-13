/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_fuzz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 03:40:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline void	*ft__handle_alignment_alloc(t_tailor *t, size_t size,
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
int	ft_tailor_buffers(t_tailor *t, size_t *sizes, t_u8 *alignment, size_t n)
{
	size_t				i;
	void				*tmp;
	t_arena_checkpoint	c;

	i = 0;
	c = ft_arena_checkpoint(&t->arena);
	t->rand_buffers.mem = ft_arena_alloc(&t->arena, n * sizeof(t_buffer), 32);
	if (!t->rand_buffers.mem)
		return (ft_arena_rewind(&t->arena, c), 0);
	t->rand_buffers.size = n;
	while (i < n)
	{
		tmp = ft__handle_alignment_alloc(t, sizes[i], alignment[i]);
		if (!tmp)
			return (ft_arena_rewind(&t->arena, c), 0);
		((t_buffer *)t->rand_buffers.mem)[i] = ft_fatptr(tmp, sizes[i]);
		++i;
	}
	return (1);
}
