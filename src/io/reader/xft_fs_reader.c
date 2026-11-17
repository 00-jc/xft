/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_reader	xft_fs_reader(t_reader_fs *ctx, t_fd fd, t_buffer buffer)
{
	static t_reader_vtable const	vtable = {
		.stream = xft__fs_reader_stream,
		.discard = xft__fs_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = xft__fs_reader_read,
		.read_all = xft__reader_read_all,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_reader_fs){.buffer = buffer, .fd = fd};
	return ((t_reader){
		.reader_ctx = ctx,
		.vtable = vtable,
	});
}
