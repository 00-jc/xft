/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_BENCH_H
# define MEM_BENCH_H

# include "xft_p_mem.h"
# include "rt.h"

void	xft_memset_test_varied(t_any ptr);
void	xft_memset_test_short_aligned(t_any ptr);
void	xft_memset_test_short_unaligned(t_any ptr);
void	xft_memset_test_medium_aligned(t_any ptr);
void	xft_memset_test_medium_unaligned(t_any ptr);
void	xft_memset_test_large_aligned(t_any ptr);
void	xft_memset_test_large_unaligned(t_any ptr);

void	xft_memcpy_test_varied(t_any ptr);
void	xft_memcpy_test_short_aligned(t_any ptr);
void	xft_memcpy_test_short_unaligned(t_any ptr);
void	xft_memcpy_test_medium_aligned(t_any ptr);
void	xft_memcpy_test_medium_unaligned(t_any ptr);
void	xft_memcpy_test_large_aligned(t_any ptr);
void	xft_memcpy_test_large_unaligned(t_any ptr);

void	xft_memmove_overlap(t_buffer *buffer, t_size shift, t_size invert,
			t_size *bytes);
void	xft_memmove_test_varied(t_any ptr);
void	xft_memmove_test_short_aligned(t_any ptr);
void	xft_memmove_test_short_unaligned(t_any ptr);
void	xft_memmove_test_medium_aligned(t_any ptr);
void	xft_memmove_test_medium_unaligned(t_any ptr);
void	xft_memmove_test_large_aligned(t_any ptr);
void	xft_memmove_test_large_unaligned(t_any ptr);

void	xft_memcpy_test_stream_1x_unaligned(t_any ptr);
void	xft_memcpy_test_stream_2x_unaligned(t_any ptr);
void	xft_memcpy_test_stream_1x_aligned(t_any ptr);
void	xft_memcpy_test_stream_2x_aligned(t_any ptr);

void	xft_memset_test_stream_1x_unaligned(t_any ptr);
void	xft_memset_test_stream_2x_unaligned(t_any ptr);
void	xft_memset_test_stream_1x_aligned(t_any ptr);
void	xft_memset_test_stream_2x_aligned(t_any ptr);

#endif
