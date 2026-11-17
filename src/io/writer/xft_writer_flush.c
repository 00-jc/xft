/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writer_flush.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_writer_flush(t_writer *w)
{
	if (w->vtable.flush == nullptr)
		__builtin_unreachable();
	return (w->vtable.flush(w));
}
