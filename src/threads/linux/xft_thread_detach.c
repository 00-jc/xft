/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_detach.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:43:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __flatten__))
void	xft_thread_detach(t_thread *__restrict__ const thread)
{
	if (__atomic_exchange_n(&thread->instance->status, THREAD_DETACHED,
			__ATOMIC_ACQ_REL) == THREAD_COMPLETED)
		xft_thread_join(thread);
}

#endif
