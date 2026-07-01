/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_bench_short.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#    +:+     +#          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:22:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memset_test_short_aligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 14;
	bufn[0] = 4;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
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

void	ft_memset_test_short_unaligned(void *ptr)
{
	t_buffer			*buffers;
	t_buffer			*out;
	t_size				n;
	t_size				bufn[3];
	static const t_u8	c = 0x42;

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	bufn[0] = 4;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
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
