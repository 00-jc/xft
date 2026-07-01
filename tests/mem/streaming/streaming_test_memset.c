/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streaming_test_memset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/streaming/streaming_test.h"

static void	fill_pattern(t_buffer buf, t_u8 seed)
{
	t_size	i;

	i = 0;
	while (i < buf.size)
	{
		buf.mem[i] = (t_u8)(seed + (i * 37U) + (i >> 3));
		i++;
	}
}

void	test_streaming_ft_memset(t_buffer buf[2], t_size off,
	t_u8 byte, t_size len)
{
	fill_pattern(buf[0], 53);
	fill_pattern(buf[1], 53);
	ft_memset(buf[0].mem + off, byte, len);
	ft_memset(buf[1].mem + off, byte, len);
	ft_pin_invariant(memcmp(buf[0].mem, buf[1].mem,
			FT_LLC_SIZE + 128ULL) == 0);
}
