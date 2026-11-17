/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_reader_discard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

__attribute__((__nonnull__(1, 3), __always_inline__, __used__))
inline t_result	xft_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	if (r->vtable.discard == nullptr)
		__builtin_unreachable();
	return (r->vtable.discard(r, limit, size));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_reader_discard_all(t_reader *r, t_size limit)
{
	if (r->vtable.discard_all == nullptr)
		__builtin_unreachable();
	return (r->vtable.discard_all(r, limit));
}
