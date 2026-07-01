/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_bench_large.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:22:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:55:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memcpy_test_large_aligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 26;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
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

void	ft_memcpy_test_large_unaligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
	t_buffer	*out;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 12;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
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
