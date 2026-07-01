/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:32:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 00:14:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((__always_inline__, pure, __nonnull__(1, 2)))
inline t_result	ft_raw_drain_check_size(void *__restrict const writer,
	t_iovec *__restrict__ bufs, t_size nbufs)
{
	t_writer *__restrict__ const		w = writer;
	t_size								offset;
	t_size								sum;
	t_size								cap;

	offset = 0;
	sum = 0;
	cap = w->as.mem_writer.external_valid - w->as.mem_writer.external_size;
	while (offset < nbufs)
		sum += bufs[offset++].size;
	if (__builtin_expect(cap < sum, 0))
		return (KO);
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline t_result	ft_raw_drain(void *__restrict const writer,
	t_iovec *__restrict__ bufs, t_size nbufs)
{
	t_writer *__restrict__ const		w = writer;
	t_size								to_copy;
	t_mem_writer *__restrict__ const	mem_w = &w->as.mem_writer;
	t_size								offset;

	if (mem_w->external == nullptr || w->buffer.mem == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(ft_raw_drain_check_size(writer, bufs, nbufs), 0))
		return (KO);
	offset = 0;
	while (offset < nbufs)
	{
		if (bufs[offset].mem == nullptr)
			__builtin_unreachable();
		to_copy = bufs[offset].size;
		ft_memcpy(mem_w->external + mem_w->external_size,
			bufs[offset++].mem, to_copy);
		mem_w->external_size += to_copy;
	}
	w->end = 0;
	return (OK);
}
