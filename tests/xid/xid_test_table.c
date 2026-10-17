/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 16:46:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/xid/xid_test.h"

static void	test_xid_table_one(const t_u32 (*set)[2], t_size len,
	bool (*is)(t_u32))
{
	t_size	i;

	xft_pin_invariant(len > 0);
	i = 0;
	while (i < len)
	{
		xft_pin_invariant(set[i][0] <= set[i][1]);
		xft_pin_invariant(i == 0 || set[i - 1][1] < set[i][0]);
		xft_pin_invariant(set[i][0] < 0x80 || is(set[i][0]));
		xft_pin_invariant(set[i][1] < 0x80 || is(set[i][1]));
		xft_pin_invariant(set[i][1] + 1 < 0x80
			|| (i + 1 < len && set[i + 1][0] == set[i][1] + 1)
			|| !is(set[i][1] + 1));
		i++;
	}
}

void	test_xid_table(void)
{
	test_xid_table_one(g_xid_start, g_xid_start_len, xft_xid_is_start);
	test_xid_table_one(g_xid_continue, g_xid_continue_len,
		xft_xid_is_continue);
}
