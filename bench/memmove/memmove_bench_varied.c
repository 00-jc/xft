/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench_varied.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 03:11:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	xft_memmove_test_varied(t_any ptr)
{
	t_buffer	*buffers;
	t_buffer	*buf;
	t_size		n;
	t_size		bufn[3];

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		buf = buffers + (n % bufn[0]);
		xft_memmove_overlap(buf, xft_tern(buf->size > 1, buf->size >> 1, 1),
			n & 1, &bufn[2]);
		__asm__("": "+r,m"(buf) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}
