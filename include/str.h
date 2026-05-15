/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:31:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 07:06:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "types.h"
# include "alloc.h"

# ifdef __clang__

typedef struct s_str
{
	size_t											size;
	size_t											capacity;
	t_u8 __attribute__	((counted_by(capacity)))	*mem;
}	t_str;

# else

typedef struct s_str
{
	size_t		size;
	size_t		capacity;
	t_u8		*mem;
}	t_str;

# endif

t_str		ft_str(size_t size);
void		ft_str_destroy(t_str *str)\
				__attribute__((__nonnull__(1)));
int			ft_str_extend(t_str *restrict const str,\
				const t_u8 *restrict const mem, size_t n)\
				__attribute__((__nonnull__(1, 2)));
int			ft_str_reserve(t_str *restrict const str, size_t n)\
				__attribute__((__nonnull__(1)));
int			ft_str_push_back(t_str *restrict const str,\
				const t_u8 byte)\
				__attribute__((__nonnull__(1)));
int			ft_str_remove(t_str *restrict const v, size_t i)\
				__attribute__((__nonnull__(1)));

#endif
