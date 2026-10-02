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
	int			(*cmp)(t_cany, t_cany);
}	t_qsort_ctx;

void	xft_qsort(t_u8 *arr, t_qsort_ctx *c, t_size l, t_size h)\
			__attribute__((__nonnull__(1, 2)));

int		xft_cmp_u64(t_cany a, t_cany b)\
			__attribute__((__nonnull__(1, 2)));

#endif
