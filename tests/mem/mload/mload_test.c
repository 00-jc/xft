/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mload_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/tests.h"

// {size, rel, u8, u16, u24, u32, u64}: the size bytes end flush against
// a guard page and read ... 0x07 0x08, so any overread faults
static const t_u64	g_mload[][7] = {
{0, 0, 0, 0, 0, 0, 0},
{1, 0, 0x08, 0, 0, 0, 0},
{1, 1, 0, 0, 0, 0, 0},
{2, 0, 0x07, 0x0807, 0, 0, 0},
{2, 1, 0x08, 0, 0, 0, 0},
{3, 0, 0x06, 0x0706, 0x080706, 0, 0},
{3, 1, 0x07, 0x0807, 0, 0, 0},
{3, 2, 0x08, 0, 0, 0, 0},
{4, 0, 0x05, 0x0605, 0x070605, 0x08070605, 0},
{4, 1, 0x06, 0x0706, 0x080706, 0, 0},
{5, 1, 0x05, 0x0605, 0x070605, 0x08070605, 0},
{8, 0, 0x01, 0x0201, 0x030201, 0x04030201, 0x0807060504030201},
{8, 1, 0x02, 0x0302, 0x040302, 0x05040302, 0},
{8, 4, 0x05, 0x0605, 0x070605, 0x08070605, 0},
{8, 7, 0x08, 0, 0, 0, 0},
{8, 8, 0, 0, 0, 0, 0},
{8, 100, 0, 0, 0, 0, 0},
};

static void	test_mload_case(const t_u64 *c, t_u8 *end)
{
	t_buffer	mem;
	t_size		rel;

	mem = xft_fatptr(end - c[0], (t_size)c[0]);
	rel = (t_size)c[1];
	xft_pin_invariant(xft_mload_rel_u8(mem, rel) == c[2]);
	xft_pin_invariant(xft_mload_rel_u16(mem, rel) == c[3]);
	xft_pin_invariant(xft_mload_rel_u24(mem, rel) == c[4]);
	xft_pin_invariant(xft_mload_rel_u32(mem, rel) == c[5]);
	xft_pin_invariant(xft_mload_rel_u64(mem, rel) == c[6]);
}

void	test_mload(t_test *t)
{
	t_buffer	page;
	t_u8		*base;
	t_size		i;

	xft_test_print(t, "Testing xft_mload_rel...\n");
	page = xft_palloc(8192);
	base = page.mem;
	xft_palloc_guard(base + 4096, 4096);
	xft_memcpy(base + 4088, "\x01\x02\x03\x04\x05\x06\x07\x08", 8);
	i = 0;
	while (i < sizeof(g_mload) / sizeof(g_mload[0]))
		test_mload_case(g_mload[i++], base + 4096);
	xft_palloc_free(page);
	xft_test_print(t, "  xft_mload_rel: OK\n");
}
