/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>

#ifdef _WIN32

__attribute__((__nonnull__(1), __flatten__))
void	xft_thread_join(t_thread *__restrict__ const thread)
{
	WaitForSingleObject((HANDLE)thread->handle, INFINITE);
	CloseHandle((HANDLE)thread->handle);
}

__attribute__((__nonnull__(1), pure))
t_thread_id	xft_thread_id(const t_thread *__restrict__ const thread)
{
	return (thread->handle);
}

#endif
