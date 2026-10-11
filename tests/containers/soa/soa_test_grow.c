/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test_grow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

#define SOA_TEST_GROW_N 1000

void	test_soa_grow(t_allocator a, const t_soa_context *ctx)
{
	t_soa			soa;
	t_soa_test_elem	e;
	t_size			i;

	soa = xft_new_soa(a, 1, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	i = 0;
	while (i < SOA_TEST_GROW_N)
	{
		e = soa_test_make(i);
		xft_pin_invariant(xft_soa_append_from_struct(a, &soa, &e, ctx));
		soa_test_check(&soa, ctx, i);
		soa_test_check(&soa, ctx, i / 2);
		++i;
	}
	xft_pin_invariant(soa.occupied_elements == SOA_TEST_GROW_N);
	xft_pin_invariant(soa.capacity_elements >= SOA_TEST_GROW_N);
	soa_test_check_aligned(&soa, ctx);
	i = 0;
	while (i < SOA_TEST_GROW_N)
		soa_test_check(&soa, ctx, i++);
	xft_destroy_soa(a, &soa);
}
