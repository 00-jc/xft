/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streaming_test_memcpy.c                            :+:      :+:    :+:   */
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

void	test_streaming_ft_memcpy(t_buffer buf[3], t_size dst,
	t_size src, t_size len)
{
	fill_pattern(buf[0], 17);
	fill_pattern(buf[1], 91);
	fill_pattern(buf[2], 91);
	ft_memcpy(buf[1].mem + dst, buf[0].mem + src, len);
	ft_memcpy(buf[2].mem + dst, buf[0].mem + src, len);
	ft_pin_invariant(memcmp(buf[1].mem, buf[2].mem,
			FT_LLC_SIZE + 128ULL) == 0);
}
