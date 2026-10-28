/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 05:40:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/xid/xid_test.h"

// {bytes little endian, cap, codepoint, len}: the cap bytes end flush
// against a guard page, so any overread faults
static const t_u32	g_utf8[][4] = {
{0x00, 0, 0, 0}, {0x00, 1, 0, 1}, {0x41, 1, 0x41, 1},
{0x7F, 1, 0x7F, 1}, {0x6241, 2, 0x41, 1}, {0x80C2, 2, 0x80, 2},
{0xBFDF, 2, 0x7FF, 2}, {0x41A9C3, 3, 0xE9, 2}, {0x80C0, 2, 0, 2},
{0xBFC1, 2, 0, 2}, {0x41C2, 2, 0, 2}, {0xC2, 1, 0, 2},
{0x80A0E0, 3, 0x800, 3}, {0xBF9FE0, 3, 0, 3}, {0xBF9FED, 3, 0xD7FF, 3},
{0x80A0ED, 3, 0, 3}, {0xBFBFED, 3, 0, 3}, {0x8080EE, 3, 0xE000, 3},
{0xBFBFEF, 3, 0xFFFF, 3}, {0xAC82E2, 3, 0x20AC, 3}, {0x82E2, 2, 0, 3},
{0x808090F0, 4, 0x10000, 4}, {0xBFBF8FF0, 4, 0, 4},
{0x80989FF0, 4, 0x1F600, 4}, {0x989FF0, 3, 0, 4},
{0xBFBF8FF4, 4, 0x10FFFF, 4}, {0x808090F4, 4, 0, 4},
{0x808080F5, 4, 0, 4}, {0x808080F8, 4, 0, 0}, {0x80, 1, 0, 0},
{0xBF, 1, 0, 0}, {0xFF, 1, 0, 0},
};

static void	test_xid_utf8(void)
{
	t_buffer	page;
	t_u8		*base;
	t_u8		*at;
	t_size		i;

	page = xft_palloc(8192);
	base = page.mem;
	xft_palloc_guard(base + 4096, 4096);
	i = 0;
	while (i < sizeof(g_utf8) / sizeof(g_utf8[0]))
	{
		at = base + 4096 - g_utf8[i][1];
		xft_memcpy(at, &g_utf8[i][0], g_utf8[i][1]);
		xft_pin_invariant(xft_xid_decode(xft_xid_load_point(at,
					g_utf8[i][1])) == g_utf8[i][2]);
		xft_pin_invariant(g_utf8[i][1] == 0
			|| xft_xid_codepoint_len(*at) == g_utf8[i][3]);
		i++;
	}
	xft_palloc_free(page);
}

void	test_xid(t_test *t)
{
	xft_test_print(t, "Testing xft_xid_is_start/continue...\n");
	test_xid_ascii();
	test_xid_points();
	test_xid_table();
	test_xid_exhaustive();
	xft_test_print(t, "  xft_xid_is_start/continue: OK\n");
	xft_test_print(t, "Testing xft_xid_decode...\n");
	test_xid_utf8();
	xft_test_print(t, "  xft_xid_decode: OK\n");
}
