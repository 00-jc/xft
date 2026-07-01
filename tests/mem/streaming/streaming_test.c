/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streaming_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/streaming/streaming_test.h"

void	test_streaming_mem(t_test *t)
{
	t_buffer	copy[3];
	t_buffer	set[2];

	ft_test_print(t, "Testing streaming ft_memcpy/ft_memset...\n");
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
	ft_test_print(t, "  streaming ft_memcpy/ft_memset: OK\n");
}
