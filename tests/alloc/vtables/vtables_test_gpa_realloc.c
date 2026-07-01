/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_gpa_realloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

__attribute__((__nonnull__(1)))
void	test_gpa_vtable_realloc(t_allocator *alloc, t_buffer buf)
{
	t_buffer	rbuf;

	rbuf = alloc->interface.realloc(alloc->allocator, buf, 512, 8);
	ft_pin_invariant_msg(rbuf.mem != nullptr,
		ft_fatptr((t_u8 *)"gpa: realloc non-null",
			sizeof("gpa: realloc non-null") - 1));
	ft_pin_invariant_msg(rbuf.size >= 512,
		ft_fatptr((t_u8 *)"gpa: realloc size",
			sizeof("gpa: realloc size") - 1));
	ft_pin_invariant_msg(rbuf.mem[0] == 0xCA,
		ft_fatptr((t_u8 *)"gpa: realloc data lo",
			sizeof("gpa: realloc data lo") - 1));
	ft_pin_invariant_msg(rbuf.mem[63] == 0xFE,
		ft_fatptr((t_u8 *)"gpa: realloc data hi",
			sizeof("gpa: realloc data hi") - 1));
	alloc->interface.free(alloc->allocator, rbuf);
	alloc->interface.destroy(alloc->allocator);
}
