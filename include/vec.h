/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:17:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "mem.h"
# include "alloc.h"
# include "types/vec_types.h"
# include <stddef.h>

t_vec			ft_vec(t_allocator allocator, t_size size, t_size type_size);
void			ft_vec_destroy(t_allocator allocator, t_vec *v)\
					__attribute__((__nonnull__(2)));

t_size			ft_vec_len(const t_vec *__restrict__ const v, t_size type_size)\
					__attribute__((__nonnull__(1), pure));

t_result		ft_vec_push_back(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					const t_u8 *__restrict__ const data, t_size type_size)\
					__attribute__((__nonnull__(2, 3)));

const void		*ft_vec_get(const t_vec *__restrict__ const vec, t_size idx,
					t_size type_size) __attribute__((__nonnull__(1),
						pure));

void			*ft_vec_get_mut(const t_vec *__restrict__ const vec, t_size idx,
					t_size type_size) __attribute__((__nonnull__(1),
						pure));

void			*ft_vec_get_last(const t_vec *__restrict__ const vec,\
					t_size type_size)\
					__attribute__((__nonnull__(1), pure));

const void		*ft_vec_peek_last(const t_vec *__restrict__ const vec,\
					t_size type_size) __attribute__((__nonnull__(1), pure));

t_result		ft_vec_reserve(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					t_size n)\
					__attribute__((__nonnull__(2)));

t_result		ft_vec_extend(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					t_buffer data)\
					__attribute__((__nonnull__(2)));

void			ft_vec_pop(t_vec *__restrict__ const v, t_size type_size)\
					__attribute__((__nonnull__(1)));

t_result		ft_vec_popmv(t_vec *__restrict__ const v, void *const dest,
					t_size type_size) __attribute__((__nonnull__(1)));

t_result		ft_vec_pop_managed(t_allocator allocator,\
					t_vec *restrict const v, size_t type_size)\
					__attribute__((__always_inline__, __nonnull__(2)));

t_result		ft_vec_remove(t_vec *__restrict__ const v, t_size i,\
					t_size type_size) __attribute__((__nonnull__(1)));

t_result		ft_vec_remove_managed(t_allocator allocator,\
					t_vec *restrict const v, size_t i, size_t type_size)\
					__attribute__((__nonnull__(2)));

void			ft_vec_clear(t_vec *__restrict__ const v)\
					__attribute__((__nonnull__(1)));

#endif
