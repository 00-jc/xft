/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_memcpy_medium.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:32:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:32:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "tailor.h"
#include "libc_bench.h"

void	xft_libc_memcpy_medium_aligned(t_any ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	buffers += 18;
	bufn[0] = 8;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = xft_tern(in->size < out->size, in->size, out->size);
		bufn[1] >>= 2;
		memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	xft_libc_memcpy_medium_unaligned(t_any ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	buffers += 4;
	bufn[0] = 8;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = xft_tern(in->size < out->size, in->size, out->size);
		bufn[1] >>= 2;
		memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}
