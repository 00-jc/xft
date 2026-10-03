/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_BENCH_H
# define VEC_BENCH_H

# include "vec.h"
# include "alloc.h"
# include "rt.h"

t_gpa	*xft_get_bench_vec_gpa(void);

void	xft_vec_bench_push_back(t_any ptr);
void	xft_vec_bench_push_back_reserved(t_any ptr);
void	xft_vec_bench_push_pop(t_any ptr);
void	xft_vec_bench_read(t_any ptr);
void	xft_vec_bench_extend(t_any ptr);
void	xft_vec_bench_remove_front(t_any ptr);

#endif
