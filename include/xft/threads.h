/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:49:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 17:38:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <xft/primitives.h>
# include <xft/alloc.h>

# ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>

typedef t_uptr			t_thread_id;

# else

typedef t_u32a			t_thread_id;

# endif

typedef void			(*t_thread_func)(t_any);

# ifndef XFT_THREAD_STACKSIZE
#  define XFT_THREAD_STACKSIZE 8388608
# endif

typedef struct s_thread_opts
{
	t_thread_func		fn;
	t_u64a				stack_size;
	t_any				argument;
}	t_thread_opts;

typedef enum e_thread_status : t_u8
{
	THREAD_RUNNING,
	THREAD_DETACHED,
	THREAD_COMPLETED,
}	t_thread_status;

typedef struct s_thread_stack
{
	t_u64a				size;
	t_thread_func		fn;
	t_any				argument;
	t_thread_id			child;
	t_thread_status		status;
	t_u8				mem[];
}	t_thread_stack;

typedef struct s_thread
{
	t_thread_stack		*stack;
}	t_thread;

#endif
