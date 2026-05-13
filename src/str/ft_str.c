/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:33:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 05:03:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

t_str	ft_str(size_t size)
{
	t_str	str;

	str.mem = ft_alloc(size + 1);
	if (__builtin_expect(!str.mem, 0))
		return ((t_str){0});
	str.size = 0;
	str.capacity = size + 1;
	str.mem[size] = 0;
	return (str);
}

__attribute__((__nonnull__(1)))
void	ft_str_destroy(t_str *str)
{
	ft_free((void **)&str->mem);
	str->size = 0;
}
