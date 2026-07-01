/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_gpa_freelist_advance.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

__attribute__((__nonnull__(1)))
void	test_gpa_freelist_advance(t_allocator *alloc)
{
	t_buffer	buf;
	int			i;

	i = -1;
	while (++i < 1000)
		alloc->interface.allocate(alloc->allocator, 64, 8);
	buf = alloc->interface.allocate(alloc->allocator, 64, 8);
	ft_pin_invariant_msg(buf.mem != nullptr,
		ft_fatptr((t_u8 *)"gpa: post-advance alloc",
			sizeof("gpa: post-advance alloc") - 1));
	alloc->interface.destroy(alloc->allocator);
}
