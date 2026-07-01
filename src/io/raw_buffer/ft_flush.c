/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 23:16:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:08:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_raw_flush(void *__restrict__ const writer)
{
	t_writer *__restrict__ const		w = writer;
	t_mem_writer *__restrict__ const	mem_w = &w->as.mem_writer;
	t_size								valid_data;

	valid_data = w->as.mem_writer.external_valid
		- w->as.mem_writer.external_size;
	if (__builtin_expect(valid_data < w->end, 0))
		return (KO);
	ft_memcpy(mem_w->external + mem_w->external_size, w->buffer.mem, w->end);
	mem_w->external_size += w->end;
	w->end = 0;
	return (OK);
}
