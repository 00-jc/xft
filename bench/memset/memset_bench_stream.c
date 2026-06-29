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

void	ft_memset_test_stream_1x_unaligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		ft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memset_test_stream_2x_unaligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 2;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		ft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memset_test_stream_1x_aligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 4;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		ft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memset_test_stream_2x_aligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 6;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		out = buffers + (n % bufn[0]);
		ft_memset(out->mem, c, out->size);
		bufn[2] += out->size;
		__asm__("": "+r,m"(out) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}
