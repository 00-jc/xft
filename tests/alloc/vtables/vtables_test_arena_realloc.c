/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_arena_realloc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

__attribute__((__nonnull__(1)))
void	test_arena_vtable_realloc(t_allocator *alloc, t_buffer buf)
{
	t_buffer	rbuf;

	rbuf = alloc->interface.realloc(alloc->allocator, buf, 256, 16);
	ft_pin_invariant_msg(rbuf.mem != nullptr,
		ft_fatptr((t_u8 *)"arena: realloc ok",
			sizeof("arena: realloc ok") - 1));
	ft_pin_invariant_msg(rbuf.size == 256,
		ft_fatptr((t_u8 *)"arena: realloc size",
			sizeof("arena: realloc size") - 1));
	ft_pin_invariant_msg(rbuf.mem[0] == 0xDE,
		ft_fatptr((t_u8 *)"arena: rdata lo", sizeof("arena: rdata lo") - 1));
	ft_pin_invariant_msg(rbuf.mem[127] == 0xAD,
		ft_fatptr((t_u8 *)"arena: rdata hi", sizeof("arena: rdata hi") - 1));
	alloc->interface.free(alloc->allocator, rbuf);
	rbuf = alloc->interface.allocate(alloc->allocator, 64, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr,
		ft_fatptr((t_u8 *)"arena: post-free alloc",
			sizeof("arena: post-free alloc") - 1));
	alloc->interface.destroy(alloc->allocator);
}
