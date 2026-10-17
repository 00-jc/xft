/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 16:46:14 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/xid/xid_test.h"

static const t_u32	g_points[][3] = {
{0x00AA, 1, 1}, {0x00B7, 0, 1}, {0x00C0, 1, 1}, {0x00D7, 0, 0},
{0x0300, 0, 1}, {0x0391, 1, 1}, {0x0660, 0, 1}, {0x200C, 0, 1},
{0x2118, 1, 1}, {0x2E2F, 0, 0}, {0x3007, 1, 1}, {0x309B, 0, 0},
{0x4E00, 1, 1}, {0xFF10, 0, 1}, {0x1D7CE, 0, 1}, {0x1F600, 0, 0},
{0xE0100, 0, 1}, {0xE01EF, 0, 1}, {0xE01F0, 0, 0}, {0x10FFFF, 0, 0},
{0x110000, 0, 0}, {0xFFFFFFFF, 0, 0},
};

void	test_xid_points(void)
{
	t_size	i;

	i = 0;
	while (i < sizeof(g_points) / sizeof(g_points[0]))
	{
		xft_pin_invariant(xft_xid_is_start(g_points[i][0])
			== (bool)g_points[i][1]);
		xft_pin_invariant(xft_xid_is_continue(g_points[i][0])
			== (bool)g_points[i][2]);
		i++;
	}
}
