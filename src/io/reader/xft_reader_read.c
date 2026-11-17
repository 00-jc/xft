/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_reader_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

__attribute__((__nonnull__(1, 3), __always_inline__, __used__))
inline t_result	xft_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	if (r->vtable.read == nullptr)
		__builtin_unreachable();
	return (r->vtable.read(r, dst, size));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_reader_read_all(t_reader *r, t_buffer dst)
{
	if (r->vtable.read_all == nullptr)
		__builtin_unreachable();
	return (r->vtable.read_all(r, dst));
}
