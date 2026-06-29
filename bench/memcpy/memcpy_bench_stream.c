/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_bench_stream.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memcpy_test_stream_1x_unaligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = ft_tern(in->size < out->size, in->size, out->size);
		ft_memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memcpy_test_stream_2x_unaligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 2;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = ft_tern(in->size < out->size, in->size, out->size);
		ft_memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memcpy_test_stream_1x_aligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 4;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = ft_tern(in->size < out->size, in->size, out->size);
		ft_memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memcpy_test_stream_2x_aligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 6;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		in = buffers + (n % bufn[0]);
		out = buffers + ((n + 1) % bufn[0]);
		bufn[1] = ft_tern(in->size < out->size, in->size, out->size);
		ft_memcpy(in->mem, out->mem, bufn[1]);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in), "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}
