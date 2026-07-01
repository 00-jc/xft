/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_u64s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

__attribute__((__nonnull__(1, 2), pure))
int	ft_cmp_u64(const void *a, const void *b)
{
	t_u64a	x;
	t_u64a	y;

	x = *(t_blk64r)a;
	y = *(t_blk64r)b;
	return ((x > y) - (x < y));
}
