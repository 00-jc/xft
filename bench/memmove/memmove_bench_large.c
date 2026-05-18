/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench_large.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 03:11:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memmove_test_large_aligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*buf;
	size_t		n;
	size_t		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 26;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		buf = buffers + (n % bufn[0]);
		ft_memmove_overlap(buf, 64, 0, &bufn[2]);
		__asm__("": "+r,m"(buf) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_memmove_test_large_unaligned(void *ptr)
{
	t_buffer	*buffers;
	t_buffer	*buf;
	size_t		n;
	size_t		bufn[3];

	n = ft_tailor_getcount(ptr);
	buffers = ft_get_all_buffers(ptr, bufn);
	buffers += 12;
	bufn[0] = 2;
	ft_pin_invariant_msg(buffers != nullptr, (char *)"NO BUFFERS");
	bufn[2] = 0;
	while (n-- > 0)
	{
		buf = buffers + (n % bufn[0]);
		ft_memmove_overlap(buf, 5, 1, &bufn[2]);
		__asm__("": "+r,m"(buf) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}
