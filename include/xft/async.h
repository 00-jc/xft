/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASYNC_H
# define ASYNC_H

# include <xft/primitives.h>
# include <xft/threads.h>
# include <xft/types/async_types.h>

t_async		xft_blocking_async(void)\
			__attribute__((__warn_unused_result__));

t_result	xft_threaded_async(t_async *self, t_allocator allocator,\
			t_sysinfo sysinfo, t_thread_opts opts)\
			__attribute__((__warn_unused_result__, __nonnull__(1)));

void		xft_threaded_async_destroy(t_allocator allocator, t_async *self)\
			__attribute__((__nonnull__(2)));

void		xft_async(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

void		xft_await(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

#endif
