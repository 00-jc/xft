/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writer_drain_all.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_writer_drain_all(t_writer *w, t_buffer data)
{
	if (w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	return (w->vtable.drain_all(w, data));
}
