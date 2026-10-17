/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test_exhaustive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 05:40:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/xid/xid_test.h"

// walks the table alongside cp, so the reference is a plain range check
static bool	xid_ref(const t_u32 (*set)[2], t_size len, t_size *at, t_u32 cp)
{
	while (*at < len && set[*at][1] < cp)
		++*at;
	return (*at < len && set[*at][0] <= cp);
}

void	test_xid_exhaustive(void)
{
	t_size	s;
	t_size	c;
	t_u32	cp;
	bool	start;

	s = 0;
	c = 0;
	cp = 0x80;
	while (cp <= 0x10FFFF)
	{
		start = xft_xid_is_start(cp);
		xft_pin_invariant(start
			== xid_ref(g_xid_start, g_xid_start_len, &s, cp));
		xft_pin_invariant(xft_xid_is_continue(cp)
			== xid_ref(g_xid_continue, g_xid_continue_len, &c, cp));
		xft_pin_invariant(!start || xft_xid_is_continue(cp));
		cp++;
	}
}
