/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "primitives.h"
# include "alloc.h"

typedef struct s_str
{
	t_size	size;
	t_size	capacity;
	t_u8	*mem;
}	t_str;

t_str		ft_str(t_allocator allocator, t_size size);
void		ft_str_destroy(t_allocator allocator, t_str *str)\
				__attribute__((__nonnull__(2)));
t_result	ft_str_extend(t_allocator allocator,\
				t_str *restrict const str,\
				const t_u8 *restrict const mem, t_size n)\
				__attribute__((__nonnull__(2, 3)));
t_result	ft_str_reserve(t_allocator allocator,\
				t_str *restrict const str, t_size n)\
				__attribute__((__nonnull__(2)));
t_result	ft_str_push_back(t_allocator allocator,\
				t_str *restrict const str, const t_u8 byte)\
				__attribute__((__nonnull__(2)));
t_result	ft_str_remove(t_str *restrict const v, t_size i)\
				__attribute__((__nonnull__(1)));

#endif
