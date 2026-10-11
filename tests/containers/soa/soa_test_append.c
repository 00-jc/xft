/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

void	test_soa_append(t_allocator a, const t_soa_context *ctx)
{
	t_soa			soa;
	t_soa_test_elem	e;
	t_any			first_ptr;
	t_size			i;

	soa = xft_new_soa(a, 8, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	first_ptr = soa.ptr;
	i = 0;
	while (i < 8)
	{
		e = soa_test_make(i);
		xft_pin_invariant(xft_soa_append_from_struct(a, &soa, &e, ctx));
		xft_pin_invariant(soa.occupied_elements == ++i);
	}
	xft_pin_invariant(soa.ptr == first_ptr);
	xft_pin_invariant(soa.capacity_elements == 8);
	i = 0;
	while (i < 8)
		soa_test_check(&soa, ctx, i++);
	xft_destroy_soa(a, &soa);
}
