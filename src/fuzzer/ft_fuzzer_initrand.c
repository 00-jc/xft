/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fuzzer_initrand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:53:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzzer.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	ft_fuzzer_init__internal(t_fuzzer *fuzz, size_t i,
	size_t n, t_arena_checkpoint c)
{
	size_t		len;
	size_t		align;

	while (i < n)
	{
		len = 1 + (ft_xoshiro256ss(fuzz->xo) % (1 << 10));
		align = 1 << (ft_xoshiro256ss(fuzz->xo) & 6);
		fuzz->buffers[i].mem = ft_arena_alloc(&fuzz->arena, len, align);
		if (fuzz->buffers[i].mem == nullptr)
			return (ft_arena_rewind(&fuzz->arena, c), KO);
		fuzz->buffers[i].size = len;
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	ft_fuzzer_add_rand(t_fuzzer *fuzz)
{
	t_arena_checkpoint	c;
	size_t				n;
	size_t				i;

	n = FT_FUZZ_MIN_INIT + (ft_xoshiro256ss(fuzz->xo) % FT_FUZZ_MAX_INIT);
	c = ft_arena_checkpoint(&fuzz->arena);
	fuzz->buffers = ft_arena_alloc(&fuzz->arena, sizeof(t_buffer) * n, 64);
	if (!fuzz->buffers)
		return (KO);
	i = fuzz->buf_n;
	fuzz->buf_n = n;
	return (ft_fuzzer_init__internal(fuzz, i, n, c));
}
