/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   :+::+:      :+::+:     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:19:03 by jaicastr          :# +#++#++#      */
/*   Updated: 2026/04/20 18:12:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_BENCH_H
# define MEM_BENCH_H

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

void	ft_memmove_overlap(t_buffer *buffer, size_t shift, size_t invert,
			size_t *bytes);
void	ft_memmove_test_varied(void *ptr);
void	ft_memmove_test_short_aligned(void *ptr);
void	ft_memmove_test_short_unaligned(void *ptr);
void	ft_memmove_test_medium_aligned(void *ptr);
void	ft_memmove_test_medium_unaligned(void *ptr);
void	ft_memmove_test_large_aligned(void *ptr);
void	ft_memmove_test_large_unaligned(void *ptr);

#endif
