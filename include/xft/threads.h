/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:49:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:26:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <xft/primitives.h>
# include <xft/alloc.h>
# include <xft/rt.h>

# ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
# endif

typedef void			(*t_thread_func)(t_any);

# ifndef XFT_THREAD_STACKSIZE
#  define XFT_THREAD_STACKSIZE 8388608
# endif

typedef struct s_thread_opts
{
	t_thread_func		fn;
	t_size				stack_size;
	t_any				argument;
}	t_thread_opts;

# if defined(_WIN32) || defined(XFT_REQUIRE_LIBC)

typedef t_uptr			t_thread_id;

typedef struct s_thread
{
	t_thread_id			handle;
}	t_thread;

# else

typedef t_u32a			t_thread_id;

typedef enum e_thread_status : t_u8
{
	THREAD_RUNNING,
	THREAD_DETACHED,
	THREAD_COMPLETED,
}	t_thread_status;

typedef struct s_thread_instance
{
	t_size				size;
	t_thread_func		fn;
	t_any				argument;
	t_thread_id			tid;
	t_thread_status		status;
	t_any				base;
}	t_thread_instance;

typedef struct s_thread
{
	t_thread_instance	*instance;
}	t_thread;

void		xft_thread_destroy(t_thread_instance *__restrict__ const instance)\
				__attribute__((__nonnull__(1), __noreturn__));

# endif

t_result	xft_thread_spawn(t_thread *__restrict__ const thread,\
				t_sysinfo sysinfo, t_thread_opts opts)\
				__attribute__((__nonnull__(1)));

void		xft_thread_join(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

void		xft_thread_detach(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

t_thread_id	xft_thread_id(const t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

#endif
