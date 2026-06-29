/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:35:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/20 01:39:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline void	ft__swap(t_u8 *a, t_u8 *b, t_u8 *buf, t_size size)
{
	ft_memcpy(buf, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, buf, size);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_ssize	ft_tailor_sort_internal(t_u8 *arr, t_qsort_ctx *c,
	t_ssize l, t_ssize h)
{
	t_u8		*pivot;
	t_ssize		i;
	t_ssize		j;

	pivot = arr + (t_size)l * c->size;
	i = l + 1;
	j = h;
	while (i <= j)
	{
		while (i <= h && c->cmp(arr + (t_size)i * c->size, pivot) <= 0)
			++i;
		while (j >= l && c->cmp(arr + (t_size)j * c->size, pivot) > 0)
			--j;
		if (i < j)
		{
			ft__swap(arr + (t_size)i * c->size,
				arr + (t_size)j * c->size, c->buf, c->size);
			++i;
			--j;
		}
	}
	ft__swap(arr + (t_size)l * c->size,
		arr + (t_size)j * c->size, c->buf, c->size);
	return (j);
}

__attribute__((__nonnull__(1, 2)))
void	ft_qsort(t_u8 *arr, t_qsort_ctx *c, t_size l, t_size h)
{
	t_ssize	p;

	if (l + 1 >= h || c->size == 0)
		return ;
	p = ft_tailor_sort_internal(arr, c, (t_ssize)l, (t_ssize)h - 1);
	if ((t_size)p > l)
		ft_qsort(arr, c, l, (t_size)p);
	ft_qsort(arr, c, (t_size)(p + 1), h);
}
