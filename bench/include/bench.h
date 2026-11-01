/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCH_H
# define BENCH_H

# include <xft/tailor.h>

void	xft_bench_memcpy(t_tailor *t);
void	xft_bench_memcpy_stream(t_tailor *t);
void	xft_bench_memmove(t_tailor *t);
void	xft_bench_memset(t_tailor *t);
void	xft_bench_memset_stream(t_tailor *t);
void	xft_bench_strlen(t_tailor *t);
void	xft_bench_gpa(t_tailor *t);
void	xft_bench_arena(t_tailor *t);
void	xft_bench_vec(t_tailor *t);
void	xft_bench_soa(t_tailor *t);
void	xft_bench_swissmap(t_tailor *t);
void	xft_bench_indexmap(t_tailor *t);
void	xft_libc_bench_memcpy(t_tailor *t);
void	xft_libc_bench_strlen(t_tailor *t);
void	xft_stl_bench_vector(t_tailor *t);
void	xft_stl_bench_map_strings(t_tailor *t);
void	xft_stl_bench_map_strings_1m(t_tailor *t);

#endif
