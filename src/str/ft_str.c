/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:33:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

t_str	ft_str(size_t size)
{
	t_buffer	buf;

	if (__builtin_expect(size == 0, 0))
		return ((t_str){0});
	buf = ft_palloc(size + 1);
	if (__builtin_expect(buf.mem == MAP_FAILED, 0))
		return ((t_str){0});
	buf.mem[0] = 0;
	return ((t_str){.size = 0, .capacity = buf.size, .mem = buf.mem});
}

__attribute__((__nonnull__(1)))
void	ft_str_destroy(t_str *str)
{
	if (str->mem)
		ft_palloc_free((t_buffer){.size = str->capacity, .mem = str->mem});
	*str = (t_str){0};
}
