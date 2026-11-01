/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_threadpool.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:54:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 20:54:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_THREADPOOL_H
# define XFT_P_THREADPOOL_H

# include <xft/threads.h>

typedef struct s_threadpool_arg
{
	t_threadpool		*tp;
	t_u32a				idx;
	t_atomic32			claimed;
	bool				pin;
}	t_threadpool_arg;

typedef struct s_tp_self
{
	t_threadpool		*tp;
	t_u32a				idx;
}	t_tp_self;

typedef enum e_tp_state : t_u8
{
	xft_tp_running,
	xft_tp_drain,
	xft_tp_cancel,
}	t_tp_state;

void		xft__free_rings(t_allocator allocator, t_threadpool *tp, t_size it)\
				__attribute__((__nonnull__(2)));

t_result	xft__init_rings(t_allocator allocator, t_threadpool *tp)\
				__attribute__((__nonnull__(2)));

void		xft__stop_threads(t_allocator allocator, t_threadpool *tp,\
				t_size it, t_tp_state mode)\
				__attribute__((__nonnull__(2)));

t_result	xft__init_threads(t_allocator allocator, t_sysinfo sysinfo,\
				t_thread_opts opts, t_threadpool *tp)\
				__attribute__((__nonnull__(4)));

void		xft__thread_routine(t_any any)\
				__attribute__((__nonnull__(1)));

t_tp_self	*xft__self(void)\
				__attribute__((__returns_nonnull__));

void		xft__global_push(t_threadpool *__restrict__ const tp,\
				t_thread_task *__restrict__ const task)\
				__attribute__((__nonnull__(1, 2)));

t_any		xft__global_pop(t_threadpool *__restrict__ const tp)\
				__attribute__((__nonnull__(1)));

void		xft__handle_completion(t_thread_task *__restrict__ const t)\
				__attribute__((__nonnull__(1)));

bool		xft__work_one(t_threadpool *__restrict__ const tp, t_u32a idx)\
				__attribute__((__nonnull__(1)));

#endif
