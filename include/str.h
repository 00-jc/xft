/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:31:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 20:40:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "types.h"
# include "alloc.h"

typedef struct s_str
{
	size_t	size;
	size_t	capacity;
	t_u8	*mem;
}	t_str;

t_str		ft_str(t_allocator allocator, size_t size);
void		ft_str_destroy(t_allocator allocator, t_str *str)\
				__attribute__((__nonnull__(2)));
int			ft_str_extend(t_allocator allocator,\
				t_str *restrict const str,\
				const t_u8 *restrict const mem, size_t n)\
				__attribute__((__nonnull__(2, 3)));
int			ft_str_reserve(t_allocator allocator,\
				t_str *restrict const str, size_t n)\
				__attribute__((__nonnull__(2)));
int			ft_str_push_back(t_allocator allocator,\
				t_str *restrict const str, const t_u8 byte)\
				__attribute__((__nonnull__(2)));
int			ft_str_remove(t_str *restrict const v, size_t i)\
				__attribute__((__nonnull__(1)));

# ifdef __cplusplus
}
# endif

#endif
