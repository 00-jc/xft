/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_gpa_freelist.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

void	test_gpa_freelist(void)
{
	t_gpa		gpa;
	t_allocator	alloc;
	t_buffer	buf;
	t_buffer	buf2;

	gpa = ft_gpa();
	alloc = ft_gpa_allocator(&gpa);
	buf = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr,
		ft_fatptr((t_u8 *)"gpa: freelist init",
			sizeof("gpa: freelist init") - 1));
	alloc.interface.free(alloc.allocator, buf);
	buf2 = alloc.interface.allocate(alloc.allocator, 64, 8);
	ft_pin_invariant_msg(buf2.mem != nullptr,
		ft_fatptr((t_u8 *)"gpa: alloc after free",
			sizeof("gpa: alloc after free") - 1));
	ft_pin_invariant_msg(buf2.mem == buf.mem,
		ft_fatptr((t_u8 *)"gpa: freelist reuse",
			sizeof("gpa: freelist reuse") - 1));
	alloc.interface.free(alloc.allocator, buf2);
	test_gpa_freelist_advance(&alloc);
}
