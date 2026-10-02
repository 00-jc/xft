/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_bench_stream.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	xft_memset_test_stream_1x_unaligned(t_any ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	bufn[0] = 2;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		xft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	xft_memset_test_stream_2x_unaligned(t_any ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	buffers += 2;
	bufn[0] = 2;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		xft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	xft_memset_test_stream_1x_aligned(t_any ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	buffers += 4;
	bufn[0] = 2;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		xft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	xft_memset_test_stream_2x_aligned(t_any ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = xft_tailor_getcount(ptr);
	buffers = xft_get_all_buffers(ptr, bufn);
	buffers += 6;
	bufn[0] = 2;
	xft_pin_invariant_msg(buffers != nullptr,
		xft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		xft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr, bufn[2]);
}
