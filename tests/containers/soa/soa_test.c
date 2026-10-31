/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

static void	test_soa_with(t_allocator a)
{
	t_buffer		ctx_buf;
	t_soa_context	*ctx;

	ctx_buf = soa_test_ctx_new(a);
	ctx = (t_soa_context *)ctx_buf.mem;
	test_soa_new(a, ctx);
	test_soa_append(a, ctx);
	test_soa_grow(a, ctx);
	test_soa_reserve(a, ctx);
	a.vtable->free(a.allocator, ctx_buf);
}

void	test_soa(t_test *t)
{
	t_gpa	gpa;
	t_arena	arena;

	xft_test_print(t, "Testing t_soa...\n");
	gpa = xft_new_gpa();
	test_soa_with(xft_gpa_allocator(&gpa));
	xft_gpa_destroy(&gpa);
	arena = xft_new_arena();
	test_soa_with(xft_arena_allocator(&arena));
	xft_destroy_arena(&arena);
	xft_test_print(t, "  t_soa: OK\n");
}
