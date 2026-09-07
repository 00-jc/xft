/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_bench_large.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:33:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:33:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "cstr_bench.h"

void	ft_strlen_test_large_aligned(t_any ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
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
		bufn[1] = ft_strlen((const char *)in->mem);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}

void	ft_strlen_test_large_unaligned(t_any ptr)
{
	t_buffer	*buffers;
	t_buffer	*in;
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
		bufn[1] = ft_strlen((const char *)in->mem);
		bufn[2] += bufn[1];
		__asm__("": "+r,m"(in) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr, bufn[2]);
}
