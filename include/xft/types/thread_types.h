/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 15:49:49 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 20:53:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_TYPES_H
# define THREAD_TYPES_H

# include <xft/primitives.h>
# include <xft/alloc.h>
# include <xft/atomics.h>
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
	bool				cpu_pinning;
	bool				use_only_physical;
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

# endif

#endif
