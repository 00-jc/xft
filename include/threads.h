/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 23:42:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 12:16:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "primitives.h"
# include "alloc.h"
# include "atomics.h"
# include "rt.h"

typedef t_i32a		t_thread_handle;
typedef t_u32a		t_tls_id;
typedef t_result	(*t_thread_func)(t_any __restrict__ arg);

# define FT_THREAD_STACKSIZE 0x1000000

typedef enum e_thread_completion_stage
{
	RUNNING,
	DETACHED,
	COMPLETED,
}	t_thread_completion_stage;

typedef struct s_thread_completion
{
	t_thread_completion_stage			completion;
	t_i32a								child_tid;
	t_i32a								parent_tid;
	t_buffer							mapped;
}	t_thread_completion;

typedef struct s_thread
{
	t_thread_handle			handle;
	t_tls_id				tls_id;
	t_thread_completion		*completion;
}	t_thread;

typedef struct s_thread_arg
{
	t_any __restrict__	arg;
	t_thread_func		fn;
}	t_thread_arg;

typedef struct s_thread_instance
{
	t_thread_arg		arg;
	t_thread_completion	completion;
}	t_thread_instance;

void		ft_thread_free_exit(t_thread_completion	*__restrict__ const comp)\
				__attribute__((__nonnull__(1), __noreturn__));

t_result	ft_thread_spawn(const t_xft_rt *__restrict__ const rt_info,\
				t_thread *__restrict__ const thread,\
				t_thread_arg *__restrict__ const arg, t_size stack_size)\
				__attribute__((__nonnull__(1, 2, 3)));

t_result	ft_thread_join(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

void		ft_thread_detach(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

t_result	ft_get_cpu_count(t_size *count)\
				__attribute__((__nonnull__(1)));

#endif
