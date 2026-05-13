/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_bench_large.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#    +:+     +#          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:22:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memset_test_large_aligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	size_t				n;
	size_t				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 26;
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

void	ft_memset_test_large_unaligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	size_t				n;
	size_t				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 26;
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
