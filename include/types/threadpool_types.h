/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADPOOL_TYPES_H
# define THREADPOOL_TYPES_H

# include "primitives.h"
# include <pthread.h>

# ifndef FT_NTHREADS
#  define FT_NTHREADS 16
# endif

typedef struct s_threadpool
{
	pthread_t			threads[FT_NTHREADS];
	pthread_mutex_t		mutex;
	pthread_cond_t		start;
	pthread_cond_t		done;
	size_t				count;
	size_t				go;
	t_u8				alive;
}	t_threadpool;

typedef void	*(*t_thread_routine)(void *)\
					__attribute__((__nonnull__(1)));

typedef struct s_thread_arg
{
	t_threadpool		*tp;
	void				*external_state;
	t_thread_routine	fn;
}	t_thread_arg;

#endif
