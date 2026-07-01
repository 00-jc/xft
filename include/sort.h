/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "primitives.h"
# include "mem.h"

typedef struct s_qsort_ctx
{
	t_u8		*buf;
	t_size		size;
	int			(*cmp)(const void *, const void *);
}	t_qsort_ctx;

void	ft_qsort(t_u8 *arr, t_qsort_ctx *c, t_size l, t_size h)\
			__attribute__((__nonnull__(1, 2)));

int		ft_cmp_u64(const void *a, const void *b)\
			__attribute__((__nonnull__(1, 2)));

#endif
