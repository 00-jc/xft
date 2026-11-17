/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_async.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/async.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_async(t_async *self, t_task *task)
{
	if (self->vtable.async == nullptr)
		__builtin_unreachable();
	self->vtable.async(self, task);
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_await(t_async *self, t_task *task)
{
	if (self->vtable.await == nullptr)
		__builtin_unreachable();
	self->vtable.await(self, task);
}
