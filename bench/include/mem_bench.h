/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   :+::+:      :+::+:     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:19:03 by jaicastr          :# +#++#++#      */
/*   Updated: 2026/06/28 22:51:33 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_BENCH_H
# define MEM_BENCH_H

# include "private/ft_p_mem.h"
# include "rt.h"

void	ft_memset_test_varied(void *ptr);
void	ft_memset_test_short_aligned(void *ptr);
void	ft_memset_test_short_unaligned(void *ptr);
void	ft_memset_test_medium_aligned(void *ptr);
void	ft_memset_test_medium_unaligned(void *ptr);
void	ft_memset_test_large_aligned(void *ptr);
void	ft_memset_test_large_unaligned(void *ptr);

void	ft_memcpy_test_varied(void *ptr);
void	ft_memcpy_test_short_aligned(void *ptr);
void	ft_memcpy_test_short_unaligned(void *ptr);
void	ft_memcpy_test_medium_aligned(void *ptr);
void	ft_memcpy_test_medium_unaligned(void *ptr);
void	ft_memcpy_test_large_aligned(void *ptr);
void	ft_memcpy_test_large_unaligned(void *ptr);

void	ft_memmove_overlap(t_buffer *buffer, t_size shift, t_size invert,
			t_size *bytes);
void	ft_memmove_test_varied(void *ptr);
void	ft_memmove_test_short_aligned(void *ptr);
void	ft_memmove_test_short_unaligned(void *ptr);
void	ft_memmove_test_medium_aligned(void *ptr);
void	ft_memmove_test_medium_unaligned(void *ptr);
void	ft_memmove_test_large_aligned(void *ptr);
void	ft_memmove_test_large_unaligned(void *ptr);

void	ft_memcpy_test_stream_1x_unaligned(void *ptr);
void	ft_memcpy_test_stream_2x_unaligned(void *ptr);
void	ft_memcpy_test_stream_1x_aligned(void *ptr);
void	ft_memcpy_test_stream_2x_aligned(void *ptr);

void	ft_memset_test_stream_1x_unaligned(void *ptr);
void	ft_memset_test_stream_2x_unaligned(void *ptr);
void	ft_memset_test_stream_1x_aligned(void *ptr);
void	ft_memset_test_stream_2x_aligned(void *ptr);

#endif
