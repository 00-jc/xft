/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_push_back(t_allocator a)
{
	t_str	s;

	s = xft_str(a, 1);
	xft_pin_invariant(xft_str_push_back(a, &s, 'h'));
	xft_pin_invariant(xft_str_push_back(a, &s, 'i'));
	xft_pin_invariant(s.size == 2);
	xft_pin_invariant(s.mem[0] == 'h');
	xft_pin_invariant(s.mem[1] == 'i');
	xft_pin_invariant(s.mem[2] == 0);
	xft_str_destroy(a, &s);
}
