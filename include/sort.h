/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:35:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/20 01:23:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "types.h"
# include "mem.h"

typedef struct s_qsort_ctx
{
	t_u8		*buf;
	size_t		size;
	int			(*cmp)(const void *, const void *);
}	t_qsort_ctx;

void	ft_qsort(t_u8 *arr, t_qsort_ctx *c, size_t l, size_t h)\
			__attribute__((__nonnull__(1, 2)));

int		ft_cmp_u64(const void *a, const void *b)\
			__attribute__((__nonnull__(1, 2)));

#endif
