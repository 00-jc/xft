/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

static void	test_soa_new_invalid(t_allocator a, const t_soa_context *ctx)
{
	t_soa_context	bad;

	xft_pin_invariant(xft_new_soa(a, 0, ctx).ptr == nullptr);
	bad = (t_soa_context){.total_struct_size = ctx->total_struct_size,
		.max_alignment = 3, .fields_count = 0};
	xft_pin_invariant(xft_new_soa(a, 4, &bad).ptr == nullptr);
	bad.max_alignment = 0;
	xft_pin_invariant(xft_new_soa(a, 4, &bad).ptr == nullptr);
	bad.max_alignment = SOA_TEST_ALIGN;
	bad.total_struct_size = 0;
	xft_pin_invariant(xft_new_soa(a, 4, &bad).ptr == nullptr);
}

void	test_soa_new(t_allocator a, const t_soa_context *ctx)
{
	t_soa	soa;

	test_soa_new_invalid(a, ctx);
	soa = xft_new_soa(a, 5, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	xft_pin_invariant(soa.occupied_elements == 0);
	xft_pin_invariant(soa.capacity_elements == 8);
	xft_pin_invariant(soa.allocator_bytes_given
		>= soa.capacity_elements * ctx->total_struct_size);
	soa_test_check_aligned(&soa, ctx);
	xft_destroy_soa(a, &soa);
	xft_pin_invariant(soa.ptr == nullptr);
	xft_pin_invariant(soa.capacity_elements == 0);
	xft_pin_invariant(soa.occupied_elements == 0);
}
