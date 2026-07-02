/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:15:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:15:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_BENCH_H
# define VEC_BENCH_H

# include "vec.h"
# include "alloc.h"
# include "rt.h"

t_gpa	*ft_get_bench_vec_gpa(void);
t_vec	*ft_get_bench_vec(void);

void	ft_vec_bench_push_back(void *ptr);
void	ft_vec_bench_push_back_reserved(void *ptr);
void	ft_vec_bench_push_pop(void *ptr);
void	ft_vec_bench_read(void *ptr);
void	ft_vec_bench_extend(void *ptr);
void	ft_vec_bench_remove_front(void *ptr);

#endif
