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

void	test_xid(t_test *t)
{
	xft_test_print(t, "Testing xft_xid_is_start/continue...\n");
	test_xid_ascii();
	test_xid_points();
	test_xid_table();
	test_xid_exhaustive();
	xft_test_print(t, "  xft_xid_is_start/continue: OK\n");
}
