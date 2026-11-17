/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASYNC_TYPES_H
# define ASYNC_TYPES_H

# include <xft/primitives.h>
# include <xft/alloc.h>
# include <xft/atomics.h>
# include <xft/types/thread_types.h>

typedef enum e_task_model : t_u8
{
	xft_must_keep_all_alive,
	xft_must_free_arg_on_completion,
	xft_must_free_task_on_completion,
	xft_must_free_task_and_arg_on_completion,
}	t_task_model;

typedef struct s_task
{
	t_result		(*f)(t_any)\
					__attribute__((__nonnull__));
	t_any			arg;
	struct s_task	*next;
	t_allocator		allocator;
	t_size			alloc_task;
	t_atomic32		completion;
	t_u32a			arg_size;
	t_result		result;
	t_task_model	arg_model;
}	t_task;

typedef struct s_threadpool
{
	t_thread			*worker_handles;
	t_ring_buffer		*worker_rings;
	t_size				n_workers;
	t_size				handle_alloc_size;
	t_size				rings_alloc_size;

	_Alignas(XFT_DESTRUCTIVE_ALIGN)
	t_atomic32			wake_up;
	t_atomic32			shut_down;
	t_atomic32			n_maybe_parked;

	_Alignas(XFT_DESTRUCTIVE_ALIGN)
	t_task				*global_q_head;
	t_task				*global_q_tail;
	t_atomic32			q_len;
	t_atomic32			n_pending;
	t_mutex				global_lock;
}	t_threadpool;

typedef struct s_async	t_async;

typedef void			(*t_async_submit)(t_async *self, t_task *task)\
						__attribute__((__nonnull__));

typedef void			(*t_async_await)(t_async *self, t_task *task)\
						__attribute__((__nonnull__));

typedef struct s_async_vtable
{
	t_async_submit	async;
	t_async_await	await;
}	t_async_vtable;

// typedef struct s_async_evented
// {
// 	t_io_uring		uring;
// }	t_async_evented;

typedef union u_async_ctx
{
	t_threadpool	threaded;
}	t_async_ctx;

typedef struct s_async
{
	t_async_vtable	vtable;
	t_async_ctx		as;
}	t_async;

#endif
