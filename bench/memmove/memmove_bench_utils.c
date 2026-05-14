/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 03:11:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

void	ft_memmove_overlap(t_buffer *buffer, size_t shift, size_t invert,
	size_t *bytes)
{
	size_t	len;

	if (buffer->size <= shift)
		return ;
	len = buffer->size - shift;
	if (invert != 0)
		ft_memmove(buffer->mem, buffer->mem + shift, len);
	else
		ft_memmove(buffer->mem + shift, buffer->mem, len);
	*bytes += len;
}
