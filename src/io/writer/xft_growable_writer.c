/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_growable_writer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/vec.h>
#include <xft/mem.h>
#include <xft/bmi.h>

__attribute__((__nonnull__(1)))
static t_result	xft__growable_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;

	return (xft_vec_extend(ctx->allocator, &ctx->vec, data));
}

__attribute__((__nonnull__(1)))
static t_result	xft__growable_writer_flush(t_writer *w)
{
	(void)w;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_writer	xft_growable_writer(t_writer_ctx_growable *ctx,
	t_allocator allocator, t_vec vec)
{
	static t_writer_vtable const	vtable = {
		.drain_all = xft__growable_writer_drain_all,
		.drain_fd = xft__growable_writer_drain_fd,
		.flush = xft__growable_writer_flush,
	};

	if (vec.buf.mem == nullptr)
		__builtin_unreachable();
	*ctx = (t_writer_ctx_growable){.allocator = allocator, .vec = vec};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
