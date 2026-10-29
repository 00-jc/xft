/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestanding_thread_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 13:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>
#include <xft/mem.h>
#include <xft/rt.h>
#include "tests/threads/thread_test.h"

__attribute__((__always_inline__, __used__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	const t_sysinfo	sysinfo = xft_get_sysinfo(sp);
	t_u8			buffer[64];
	t_writer		writer;

	writer = xft_get_fs_writer(xft_fatptr(buffer, sizeof(buffer)),
			xft_get_stdout());
	xft_pin_invariant_msg(xft_start_tls_for_main_thread(sysinfo) == OK,
		xft_fatptr((t_u8 *)"tls start", sizeof("tls start") - 1));
	test_thread_join(sysinfo);
	test_thread_tls(sysinfo);
	test_thread_detach(sysinfo);
	test_thread_signal(sysinfo);
	xft_writer_write(&writer, xft_fatptr((t_u8 *)"xft_thread: OK\n",
			sizeof("xft_thread: OK\n") - 1));
	xft_writer_flush(&writer);
	xft_exit_process(0);
}
