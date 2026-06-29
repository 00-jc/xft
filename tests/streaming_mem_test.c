/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streaming_mem_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:08:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"
#include "private/ft_p_mem.h"
#include "alloc/page_alloc.h"

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

static void	test_streaming_ft_memcpy(t_buffer buf[3], t_size dst,
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

static void	test_streaming_ft_memset(t_buffer buf[2], t_size off,
	t_u8 byte, t_size len)
{
	fill_pattern(buf[0], 53);
	fill_pattern(buf[1], 53);
	ft_memset(buf[0].mem + off, byte, len);
	ft_memset(buf[1].mem + off, byte, len);
	ft_pin_invariant(memcmp(buf[0].mem, buf[1].mem,
			FT_LLC_SIZE + 128ULL) == 0);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	t_buffer	copy[3];
	t_buffer	set[2];

	ft_printf("Testing streaming ft_memcpy/ft_memset...\n");
	copy[0] = ft_palloc(FT_LLC_SIZE + 128ULL);
	copy[1] = ft_palloc(FT_LLC_SIZE + 128ULL);
	copy[2] = ft_palloc(FT_LLC_SIZE + 128ULL);
	set[0] = ft_palloc(FT_LLC_SIZE + 128ULL);
	set[1] = ft_palloc(FT_LLC_SIZE + 128ULL);
	ft_pin_invariant(copy[0].mem && copy[1].mem && copy[2].mem);
	ft_pin_invariant(set[0].mem && set[1].mem);
	test_streaming_ft_memcpy(copy, 0, 0, FT_LLC_SIZE + 4096ULL);
	test_streaming_ft_memcpy(copy, 5, 3, FT_LLC_SIZE + 4096ULL);
	test_streaming_ft_memcpy(copy, 17, 9, FT_LLC_SIZE + 4169ULL);
	test_streaming_ft_memset(set, 0, 0xA5, FT_LLC_SIZE + 4096ULL);
	test_streaming_ft_memset(set, 7, 0x3C, FT_LLC_SIZE + 4096ULL);
	test_streaming_ft_memset(set, 19, 0xFF, FT_LLC_SIZE + 4187ULL);
	ft_palloc_free(copy[0]);
	ft_palloc_free(copy[1]);
	ft_palloc_free(copy[2]);
	ft_palloc_free(set[0]);
	ft_palloc_free(set[1]);
	ft_printf("  streaming ft_memcpy/ft_memset: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
