/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_reader_stream.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

__attribute__((__nonnull__(1, 2, 4), __always_inline__, __used__))
inline t_result	xft_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	if (r->vtable.stream == nullptr)
		__builtin_unreachable();
	return (r->vtable.stream(r, w, limit, size));
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_result	xft_reader_stream_all(t_reader *r, t_writer *w,
	t_size limit)
{
	if (r->vtable.stream_all == nullptr)
		__builtin_unreachable();
	return (r->vtable.stream_all(r, w, limit));
}
