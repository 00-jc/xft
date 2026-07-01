/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_palloc_realloc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

__attribute__((__nonnull__(1)))
void	test_palloc_vtable_realloc(t_allocator *alloc, t_buffer buf)
{
	t_buffer	rbuf;

	rbuf = alloc->interface.realloc(alloc->allocator, buf, 4096, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr,
		ft_fatptr((t_u8 *)"palloc: realloc ok",
			sizeof("palloc: realloc ok") - 1));
	ft_pin_invariant_msg(rbuf.size >= 4096,
		ft_fatptr((t_u8 *)"palloc: realloc size",
			sizeof("palloc: realloc size") - 1));
	ft_pin_invariant_msg(rbuf.mem[0] == 0xAB,
		ft_fatptr((t_u8 *)"palloc: rdata lo",
			sizeof("palloc: rdata lo") - 1));
	ft_pin_invariant_msg(rbuf.mem[63] == 0xCD,
		ft_fatptr((t_u8 *)"palloc: rdata hi",
			sizeof("palloc: rdata hi") - 1));
	alloc->interface.free(alloc->allocator, rbuf);
}
