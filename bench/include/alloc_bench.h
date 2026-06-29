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

t_gpa	*ft_get_bench_gpa(void);
t_arena	*ft_get_bench_arena(void);

void	ft_gpa_bench_8(void *ptr);
void	ft_gpa_bench_64(void *ptr);
void	ft_gpa_bench_512(void *ptr);
void	ft_gpa_bench_8k(void *ptr);
void	ft_gpa_bench_varied(void *ptr);
void	ft_gpa_bench_random(void *ptr);
void	ft_gpa_bulk_bench_64(void *ptr);
void	ft_gpa_bulk_bench_512(void *ptr);
void	ft_gpa_bulk_bench_mixed(void *ptr);

void	ft_arena_bench_8(void *ptr);
void	ft_arena_bench_64(void *ptr);
void	ft_arena_bench_512(void *ptr);
void	ft_arena_bench_varied(void *ptr);
void	ft_arena_bench_random(void *ptr);

#endif
