/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test_reserve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

static void	soa_test_fill(t_soa *soa, const t_soa_context *ctx,
	t_size from, t_size to)
{
	t_soa_test_elem	e;

	while (from < to)
	{
		e = soa_test_make(from++);
		xft_soa_append_from_struct_unchecked(soa, &e, ctx);
	}
}

void	test_soa_reserve(t_allocator a, const t_soa_context *ctx)
{
	t_soa	soa;
	t_any	first_ptr;
	t_size	i;

	soa = xft_new_soa(a, 8, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	soa_test_fill(&soa, ctx, 0, 3);
	first_ptr = soa.ptr;
	xft_pin_invariant(xft_soa_reserve(a, &soa, ctx, 5));
	xft_pin_invariant(soa.ptr == first_ptr && soa.capacity_elements == 8);
	xft_pin_invariant(xft_soa_reserve(a, &soa, ctx, 100));
	xft_pin_invariant(soa.capacity_elements >= 103);
	xft_pin_invariant(soa.occupied_elements == 3);
	soa_test_check_aligned(&soa, ctx);
	i = 0;
	while (i < 3)
		soa_test_check(&soa, ctx, i++);
	soa_test_fill(&soa, ctx, 3, 103);
	i = 0;
	while (i < 103)
		soa_test_check(&soa, ctx, i++);
	xft_destroy_soa(a, &soa);
}
