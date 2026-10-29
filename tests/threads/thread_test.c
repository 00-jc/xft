/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"
#include "tests/tests.h"

#ifdef __linux__

void	test_threads(t_test *t, t_sysinfo sysinfo)
{
	xft_test_print(t, "Testing xft_thread...\n");
	test_thread_join(sysinfo);
	test_thread_tls(sysinfo);
	test_thread_detach(sysinfo);
	xft_test_print(t, "  xft_thread: OK\n");
}

#else

void	test_threads(t_test *t, t_sysinfo sysinfo)
{
	(void)t;
	(void)sysinfo;
}

#endif
