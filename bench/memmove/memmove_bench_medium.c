/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench_medium.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 03:11:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memmove_test_medium_aligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*buf;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 18;
	bufn[0] = 8;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		buf = buffers + (n % bufn[0]);
		ft_memmove_overlap(buf, 8, 0, &bufn[2]);
		__asm__("": "+r,m"(buf) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memmove_test_medium_unaligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*buf;
	t_size		n;
	t_size		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 4;
	bufn[0] = 8;
	ft_pin_invariant_msg(buffers != nullptr,
		ft_fatptr((t_u8 *)"NO BUFFERS", 10));
	bufn[2] = 0;
	while (n-- > 0)
	{
		buf = buffers + (n % bufn[0]);
		ft_memmove_overlap(buf, 3, 1, &bufn[2]);
		__asm__("": "+r,m"(buf) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}
