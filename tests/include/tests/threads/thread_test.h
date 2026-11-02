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
# include <xft/alloc.h>
# include <xft/cstr.h>
# include <xft/xft_p_threadpool.h>
# ifdef __linux__
#  include <xft/xft_p_syscalls.h>
# endif
# include <stdatomic.h>

typedef struct s_signal_test
{
	t_atomic32	wake;
	t_atomic32	go;
	t_atomic32	progress;
	t_atomic32	ready;
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

typedef enum e_pool_test_conf : t_u32
{
	POOL_TEST_OUTER = 64,
	POOL_TEST_INNER = 8,
	POOL_TEST_BIG_OUTER = 2,
	POOL_TEST_BIG_INNER = 600,
	POOL_TEST_TASKS = 2048,
	POOL_TEST_OWNED = 64,
	POOL_TEST_PRODUCERS = 4,
	POOL_TEST_ROUNDS = 10,
	POOL_TEST_SPIN = 20000,
}	t_pool_test_conf;

typedef struct s_pool_job
{
	struct s_pool_test	*s;
	t_u32a				idx;
}	t_pool_job;

typedef struct s_pool_test
{
	t_threadpool		tp;
	t_allocator			alloc;
	t_atomic32			count;
	t_atomic32			bad_self;
	t_atomic32			submitted;
	t_u32a				n_outer;
	t_u32a				n_inner;
	t_pool_job			jobs[POOL_TEST_OUTER];
	t_thread_task		outer[POOL_TEST_OUTER];
	t_thread_task		inner[POOL_TEST_TASKS];
}	t_pool_test;

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
void	thread_signal_spawn(t_thread *__restrict__ const thread,\
			t_sysinfo sysinfo, t_signal_test *__restrict__ const s,\
			t_thread_func fn);
void	thread_signal_rounds(t_sysinfo sysinfo,\
			t_signal_test *__restrict__ const s, const t_u32a n,\
			const bool for_all);
void	thread_detach_run(t_u32a *__restrict__ const flags);
void	thread_detach_spawn(t_thread *__restrict__ const thread,\
			t_sysinfo sysinfo, t_u32a *__restrict__ const flags);
void	test_thread_pool(t_sysinfo sysinfo);
void	pool_assert(bool ok, const char *msg);
void	pool_task_set(t_thread_task *__restrict__ const t,\
			t_result (*f)(t_any), t_any arg, t_allocator alloc);
void	pool_spin(void);
void	pool_check_tasks(t_thread_task *__restrict__ const t, t_u32a n,\
			bool wait);
void	pool_round_cancel(t_pool_test *__restrict__ const s,\
			t_sysinfo sysinfo);
void	pool_round_wait(t_pool_test *__restrict__ const s,\
			t_sysinfo sysinfo);
void	pool_round_wait_all(t_pool_test *__restrict__ const s,\
			t_sysinfo sysinfo);
void	pool_round_wait_all_mp(t_pool_test *__restrict__ const s,\
			t_sysinfo sysinfo);
void	pool_round_fair(t_pool_test *__restrict__ const s,\
			t_sysinfo sysinfo);

#endif
