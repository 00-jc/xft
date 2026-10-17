/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xid_test_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:40:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 05:40:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/xid/xid_test.h"

void	test_xid_ascii(void)
{
	t_u32	c;

	c = 0;
	while (c < 0x80)
	{
		xft_pin_invariant(xft_xid_is_start(c)
			== ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
				|| c == '_'));
		xft_pin_invariant(xft_xid_is_continue(c)
			== ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
				|| (c >= '0' && c <= '9') || c == '_'));
		c++;
	}
}
