/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threadpool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:24:22 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 18:19:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "hint.h"

__attribute__((__nonnull__(1)))
static void	unlock_mutex(void *arg)
{
	pthread_mutex_unlock((pthread_mutex_t *)arg);
}

__attribute__((__nonnull__(1)))
void	ft_threadpool_destroy(t_threadpool *tp, size_t i)
{
	while (i-- > 0)
	{
		pthread_cancel(tp->threads[i]);
		pthread_join(tp->threads[i], nullptr);
	}
	pthread_mutex_destroy(&tp->mutex);
	pthread_cond_destroy(&tp->start);
	pthread_cond_destroy(&tp->done);
}

__attribute__((__nonnull__(1)))
void	*ft_thread_run(void *arg)
{
	t_thread_arg			*ta;
	volatile size_t			gen;
	void					*ret;

	ta = (t_thread_arg *)arg;
	ret = (void *)1;
	gen = 0;
	while (ret)
	{
		pthread_mutex_lock(&ta->tp->mutex);
		pthread_cleanup_push(unlock_mutex, &ta->tp->mutex);
		while (ta->tp->go == gen)
			pthread_cond_wait(&ta->tp->start, &ta->tp->mutex);
		gen = ta->tp->go;
		pthread_cleanup_pop(0);
		pthread_mutex_unlock(&ta->tp->mutex);
		ret = ta->fn(ta->external_state);
		pthread_mutex_lock(&ta->tp->mutex);
		--ta->tp->count;
		if (ta->tp->count == 0)
			pthread_cond_signal(&ta->tp->done);
		pthread_mutex_unlock(&ta->tp->mutex);
	}
	return (ret);
}

__attribute__((__nonnull__(1)))
void	ft_threadpool_start(t_threadpool *tp)
{
	pthread_mutex_lock(&tp->mutex);
	while (tp->count > 0)
		pthread_cond_wait(&tp->done, &tp->mutex);
	tp->count = FT_NTHREADS;
	tp->go++;
	pthread_cond_broadcast(&tp->start);
	pthread_mutex_unlock(&tp->mutex);
}

__attribute__((__nonnull__(1, 2)))
t_u32a	ft_threadpool_new(t_threadpool *tp, t_thread_arg *arg)
{
	size_t			i;

	i = 0;
	tp->count = 0;
	tp->go = 0;
	tp->alive = 0;
	ft_pin_invariant_msg(FT_NTHREADS,
		(char *)__FILE__":NTHREADS cannot be 0");
	pthread_mutex_init(&tp->mutex, nullptr);
	pthread_cond_init(&tp->start, nullptr);
	pthread_cond_init(&tp->done, nullptr);
	while (i < FT_NTHREADS)
	{
		if (pthread_create(tp->threads + i, nullptr, ft_thread_run, (void *)arg))
			return ((void)(pthread_mutex_unlock(&tp->mutex)),
				ft_threadpool_destroy(tp, i), 0);
		++i;
	}
	tp->alive = 1;
	return (1);
}
