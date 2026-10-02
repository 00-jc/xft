/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fuzzer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzzer.h"

t_fuzzer	xft_fuzzer_new(t_arena arena)
{
	t_fuzzer	fz;

	fz.arena = arena;
	fz.buffers = nullptr;
	fz.buf_n = 0;
	xft_xoshiro_init(fz.xo);
	return (fz);
}

__attribute__((__nonnull__(1)))
void	xft_fuzzer_destroy(t_fuzzer *f)
{
	xft_destroy_arena(&f->arena);
}
