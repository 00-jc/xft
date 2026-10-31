/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/atomics/ring_buffer/ring_buffer_test.h"

void	test_ring_buffer(t_test *t)
{
	xft_test_print(t, "Testing ring buffer...\n");
	test_ring_buffer_init();
	test_ring_buffer_fifo();
	xft_test_print(t, "  ring buffer: OK\n");
}
