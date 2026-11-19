/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_reader_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__reader_stream_all(t_reader *r, t_writer *w, t_size limit)
{
	t_size		n;
	t_result	ok;

	if (r->vtable.stream == nullptr)
		__builtin_unreachable();
	ok = r->vtable.stream(r, w, limit, &n);
	return ((t_result){.ok = ok.ok && n == limit,
		.err = xft_tern(ok.ok && n != limit, xft_err_eof, ok.err)});
}

__attribute__((__nonnull__(1)))
t_result	xft__reader_read_all(t_reader *r, t_buffer dst)
{
	t_size		n;
	t_result	ok;

	if (r->vtable.read == nullptr)
		__builtin_unreachable();
	ok = r->vtable.read(r, dst, &n);
	return ((t_result){.ok = ok.ok && n == dst.size,
		.err = xft_tern(ok.ok && n != dst.size, xft_err_eof, ok.err)});
}

__attribute__((__nonnull__(1)))
t_result	xft__reader_discard_all(t_reader *r, t_size limit)
{
	t_size		n;
	t_result	ok;

	if (r->vtable.discard == nullptr)
		__builtin_unreachable();
	ok = r->vtable.discard(r, limit, &n);
	return ((t_result){.ok = ok.ok && n == limit,
		.err = xft_tern(ok.ok && n != limit, xft_err_eof, ok.err)});
}
