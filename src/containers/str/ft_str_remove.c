/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:49:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 05:56:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

__attribute__((__nonnull__(1)))
t_result	ft_str_remove(t_str *restrict const v, t_size i)
{
	t_u8	*start;
	t_size	len;

	if (!v->mem || v->size <= i)
		return (KO);
	start = v->mem + i;
	len = v->size - i;
	ft_memmove(start, start + 1, len);
	--v->size;
	return (OK);
}
