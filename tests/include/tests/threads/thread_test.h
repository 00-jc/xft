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

void	test_thread_join(t_sysinfo sysinfo);
void	test_thread_tls(t_sysinfo sysinfo);
void	test_thread_detach(t_sysinfo sysinfo);
void	test_thread_signal(t_sysinfo sysinfo);
void	thread_detach_run(t_u32a *__restrict__ const flags);
void	thread_detach_spawn(t_thread *__restrict__ const thread,\
			t_sysinfo sysinfo, t_u32a *__restrict__ const flags);

#endif
