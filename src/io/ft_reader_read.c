/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 14:21:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

__attribute__((__always_inline__, __nonnull__(1, 2, 4)))
inline t_result	ft_read_from_reader(t_reader *__restrict__ const reader,
	t_u8 *__restrict__ const dst, const t_size len,
	t_size *__restrict__ const total)
{
	t_size	read;
	t_size	step;
	t_size	n;

	if (reader->buffer.mem == nullptr)
		__builtin_unreachable();
	if (reader->buffer.size <= len)
		return (reader->vtable->unbufered_fill(reader, dst, len, total));
	read = 0;
	while (read != len)
	{
		if (__builtin_expect(reader->end == reader->valid
				&& reader->vtable->fill(reader) == KO, 0))
			return (KO);
		if (__builtin_expect(reader->valid == 0, 0))
			break ;
		step = reader->valid - reader->end;
		n = ft_tern(len - read < step, len - read, step);
		ft_memcpy(dst + read, reader->buffer.mem + reader->end, n);
		read += n;
		reader->end += n;
	}
	*total = read;
	return (OK);
}
