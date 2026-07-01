/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_palloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

void	test_palloc_vtable(void)
{
	t_allocator	alloc;
	t_buffer	buf;

	alloc = ft_new_page_alloc();
	buf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr,
		ft_fatptr((t_u8 *)"palloc: alloc non-null",
			sizeof("palloc: alloc non-null") - 1));
	ft_pin_invariant_msg(buf.size >= 64,
		ft_fatptr((t_u8 *)"palloc: alloc size",
			sizeof("palloc: alloc size") - 1));
	buf.mem[0] = 0xAB;
	buf.mem[63] = 0xCD;
	ft_pin_invariant_msg(buf.mem[0] == 0xAB,
		ft_fatptr((t_u8 *)"palloc: rw lo", sizeof("palloc: rw lo") - 1));
	ft_pin_invariant_msg(buf.mem[63] == 0xCD,
		ft_fatptr((t_u8 *)"palloc: rw hi", sizeof("palloc: rw hi") - 1));
	test_palloc_vtable_realloc(&alloc, buf);
}
