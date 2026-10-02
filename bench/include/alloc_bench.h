/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_bench.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:51:41 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_BENCH_H
# define ALLOC_BENCH_H

# include "alloc.h"
# include "rt.h"

t_gpa	*xft_get_bench_gpa(void);
t_arena	*xft_get_bench_arena(void);

void	xft_gpa_bench_8(t_any ptr);
void	xft_gpa_bench_64(t_any ptr);
void	xft_gpa_bench_512(t_any ptr);
void	xft_gpa_bench_8k(t_any ptr);
void	xft_gpa_bench_varied(t_any ptr);
void	xft_gpa_bench_random(t_any ptr);
void	xft_gpa_bulk_bench_64(t_any ptr);
void	xft_gpa_bulk_bench_512(t_any ptr);
void	xft_gpa_bulk_bench_mixed(t_any ptr);

void	xft_arena_bench_8(t_any ptr);
void	xft_arena_bench_64(t_any ptr);
void	xft_arena_bench_512(t_any ptr);
void	xft_arena_bench_varied(t_any ptr);
void	xft_arena_bench_random(t_any ptr);

#endif
