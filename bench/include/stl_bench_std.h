/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_std.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_STD_H
# define STL_BENCH_STD_H

/* read by both the C driver and the C++ std:: side, so no xft headers */
# include <stdint.h>

/* mirror the xft side's workloads; stl_bench_run.c asserts they match */
# define STL_BENCH_FILL			4096
# define STL_BENCH_KEYS			8192
# define STL_BENCH_LARGE_FILL	1048576
# define STL_BENCH_READ_FILL	1024
# define STL_BENCH_RMF_LEN		256

/* a string both sides read: std::string_view, or t_buffer on the xft side */
typedef struct s_stl_str
{
	uint64_t		size;
	const uint8_t	*mem;
}	t_stl_str;

void	xft_std_vector_bench_push_back(void *ptr);
void	xft_std_vector_bench_push_back_reserved(void *ptr);
void	xft_std_vector_bench_push_pop(void *ptr);
void	xft_std_vector_bench_read(void *ptr);
void	xft_std_vector_bench_extend(void *ptr);
void	xft_std_vector_bench_remove_front(void *ptr);

void	xft_std_umap_bench_insert_grow(void *ptr);
void	xft_std_umap_bench_insert_reserved(void *ptr);
void	xft_std_umap_bench_lookup_hit(void *ptr);
void	xft_std_umap_bench_lookup_miss(void *ptr);
void	xft_std_umap_bench_delete_insert(void *ptr);
void	xft_std_umap_bench_large_lookup_hit(void *ptr);
void	xft_std_umap_bench_large_lookup_miss(void *ptr);
void	xft_std_umap_bench_large_delete_insert(void *ptr);

void	xft_std_umap_str_bench_insert_grow(void *ptr);
void	xft_std_umap_str_bench_insert_reserved(void *ptr);
void	xft_std_umap_str_bench_lookup_hit(void *ptr);
void	xft_std_umap_str_bench_lookup_miss(void *ptr);
void	xft_std_umap_str_bench_delete_insert(void *ptr);
void	xft_std_umap_str_bench_large_lookup_hit(void *ptr);
void	xft_std_umap_str_bench_large_lookup_miss(void *ptr);
void	xft_std_umap_str_bench_large_delete_insert(void *ptr);

#endif
