/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/13 15:41:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1)))
void	ft_vec_free(t_vec *v)
{
	ft_palloc_free(v->buf);
	*v = (t_vec){0};
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_vec_clear(t_vec *restrict const v)
{
	v->size = 0;
}
