/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_TEST_H
# define THREAD_TEST_H

# include <xft/atomics.h>
# include <xft/threads.h>
# include <xft/hint.h>
# include <xft/mem.h>
# ifdef __linux__
#  include <xft/xft_p_syscalls.h>
# endif
# include <stdatomic.h>

typedef struct s_signal_test
{
	t_atomic32	wake;
	t_atomic32	go;
	t_atomic32	progress;
	t_u32a		rounds;
}	t_signal_test;

typedef enum e_rb_test_conf : t_u32
{
	RB_TEST_ITEMS = 16384,
	RB_TEST_SIZE = 64,
	RB_TEST_THREADS = 4,
	RB_BACKOFF_THREADS = 3,
	RB_BACKOFF_SIZE = RB_BACKOFF_THREADS + 1,
	RB_BACKOFF_DELAY = 1u << 20,
}	t_rb_test_conf;

typedef struct s_ring_buffer_test
{
	t_ring_buffer	rb;
	t_atomic32		next;
	t_atomic32		consumed;
	t_atomic32		done;
	t_atomic32		full;
	t_atomic32		seen[RB_TEST_ITEMS];
	t_u8			items[RB_TEST_ITEMS];
}	t_ring_buffer_test;

typedef struct s_rb_backoff_test
{
	t_ring_buffer	rb;
	t_atomic32		started;
	t_atomic32		returned;
	t_atomicptr		got[RB_BACKOFF_THREADS];
	t_thread		threads[RB_BACKOFF_THREADS];
	t_u8			items[RB_BACKOFF_THREADS + 1];
}	t_rb_backoff_test;

void	test_thread_join(t_sysinfo sysinfo);
void	test_thread_tls(t_sysinfo sysinfo);
void	test_thread_detach(t_sysinfo sysinfo);
void	test_thread_signal(t_sysinfo sysinfo);
void	test_thread_ring_buffer(t_sysinfo sysinfo);
void	test_thread_ring_buffer_backoff(t_sysinfo sysinfo);
void	thread_rb_backoff_start(t_rb_backoff_test *__restrict__ const s,\
			t_sysinfo sysinfo, const bool steal);
void	thread_rb_backoff_finish(t_rb_backoff_test *__restrict__ const s,\
			t_atomicptr *__restrict__ const slots);
void	thread_detach_run(t_u32a *__restrict__ const flags);
void	thread_detach_spawn(t_thread *__restrict__ const thread,\
			t_sysinfo sysinfo, t_u32a *__restrict__ const flags);

#endif
