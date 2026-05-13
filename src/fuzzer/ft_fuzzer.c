/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fuzzer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:50:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzzer.h"

t_fuzzer	ft_fuzzer_new(t_arena arena)
{
	t_fuzzer	fz;

	fz.arena = arena;
	fz.buffers = nullptr;
	fz.buf_n = 0;
	ft_xoshiro_init(fz.xo);
	return (fz);
}

__attribute__((__nonnull__(1)))
void	ft_fuzzer_destroy(t_fuzzer *f)
{
	ft_destroy_arena(&f->arena);
}
