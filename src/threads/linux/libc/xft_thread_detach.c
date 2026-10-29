/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_detach.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC
#  include <pthread.h>

__attribute__((__nonnull__(1), __flatten__))
void	xft_thread_detach(t_thread *__restrict__ const thread)
{
	pthread_detach((pthread_t)thread->handle);
}

# endif

#endif
