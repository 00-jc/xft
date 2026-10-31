/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_clone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 03:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 03:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

static void	clone_check(t_allocator a, t_size n)
{
	t_buffer	src;
	t_buffer	dst;
	t_size		i;

	if (a.vtable == nullptr || a.vtable->allocate == nullptr
		|| a.vtable->clone == nullptr || a.vtable->free == nullptr)
		__builtin_unreachable();
	src = a.vtable->allocate(a.allocator, n, 64);
	xft_pin_invariant_msg(src.mem != nullptr,
		xft_fatptr((t_u8 *)"clone: src", sizeof("clone: src") - 1));
	i = n;
	while (i-- > 0)
		src.mem[i] = (t_u8)(i * 31 + 7);
	dst = a.vtable->clone(a, xft_fatptr(src.mem, n));
	xft_pin_invariant_msg(dst.mem != nullptr && dst.mem != src.mem
		&& dst.size >= n, xft_fatptr((t_u8 *)"clone: new buffer",
			sizeof("clone: new buffer") - 1));
	xft_pin_invariant_msg(!((t_uptr)dst.mem & (__GCC_CONSTRUCTIVE_SIZE - 1)),
		xft_fatptr((t_u8 *)"clone: aligned", sizeof("clone: aligned") - 1));
	xft_pin_invariant_msg(xft_memcmp(dst.mem, src.mem, n) == 0,
		xft_fatptr((t_u8 *)"clone: data", sizeof("clone: data") - 1));
	a.vtable->free(a.allocator, dst);
	a.vtable->free(a.allocator, src);
}

static void	clone_sizes(t_allocator a)
{
	static const t_size	sizes[] = {1, 7, 64, 100, 4096, 70000, 3000000};
	t_size				i;

	if (a.vtable == nullptr)
		__builtin_unreachable();
	i = 0;
	while (i < sizeof(sizes) / sizeof(sizes[0]))
		clone_check(a, sizes[i++]);
	if (a.vtable->destroy != nullptr)
		a.vtable->destroy(a.allocator);
}

static void	clone_ts(void)
{
	t_ts_gpa		gpa;
	t_ts_reporta	rep;
	t_ts_arena		arena;

	gpa = xft_new_ts_gpa();
	rep = xft_new_ts_reporta();
	arena = xft_new_ts_arena();
	clone_sizes(xft_ts_gpa_allocator(&gpa));
	clone_sizes(xft_ts_reporta_allocator(&rep));
	clone_sizes(xft_ts_arena_allocator(&arena));
}

void	test_clone_vtable(void)
{
	t_gpa		gpa;
	t_reporta	rep;
	t_arena		arena;

	gpa = xft_new_gpa();
	rep = xft_new_reporta();
	arena = xft_new_arena();
	clone_sizes(xft_gpa_allocator(&gpa));
	clone_sizes(xft_reporta_allocator(&rep));
	clone_sizes(xft_arena_allocator(&arena));
	clone_sizes(xft_page_allocator());
	clone_ts();
}
