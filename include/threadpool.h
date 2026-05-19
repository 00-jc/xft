/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:20:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 16:41:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADPOOL_H
# define THREADPOOL_H

# include "types.h"
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

void		ft_threadpool_destroy(t_threadpool *tp, size_t i)\
				__attribute__((__nonnull__(1)));
void		*ft_thread_run(void *arg)\
				__attribute__((__nonnull__(1)));
void		ft_threadpool_start(t_threadpool *tp)\
				__attribute__((__nonnull__(1)));
void		ft_threadpool_join(t_threadpool *tp, void **results)\
				__attribute__((__nonnull__(1, 2)));
t_u32a		ft_threadpool_new(t_threadpool *tp, t_thread_arg *arg)\
				__attribute__((__nonnull__(1, 2)));
void		ft_threadpool_wait(t_threadpool *tp)\
				__attribute__((__nonnull__(1)));

#endif
