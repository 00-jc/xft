/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 02:57:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"
#include "types/atomic_types.h"
#include "xft.h"
#include "threads.h"

static void	ft_print_stdout(const char *__restrict__ const msg)
{
	t_writer	w;
	t_u8		buf[1024 << 1];

	w = ft_get_fs_writer(ft_fatptr(buf, 64), ft_get_stdout());
	ft_writer_write(&w, ft_fatptr((t_u8 *)msg, ft_strlen(msg)));
	(void)ft_writer_flush(&w);
}

static void	ft_print_stderr(const char *__restrict__ const msg)
{
	t_writer	w;
	t_u8		buf[1024 << 1];

	w = ft_get_fs_writer(ft_fatptr(buf, 64), ft_get_stderr());
	ft_writer_write(&w, ft_fatptr((t_u8 *)msg, ft_strlen(msg)));
	(void)ft_writer_flush(&w);
}

static t_result	say_hello(t_any __restrict__ arg)
{
	t_u64a		x;

	(void)arg;
	x = 100;
	while (x--)
		ft_print_stdout("Hello from thread!\n");
	return (OK);
}

__attribute__((nonnull(1)))
void	ft_main(const t_any *__restrict__ const sp)
{
	t_xft_rt		rt_info;
	t_thread		t;
	t_thread_arg	targ;
	t_u64			x;

	x = 100;
	rt_info = ft_get_rt(sp);
	targ = (t_thread_arg){.arg = nullptr, .fn = say_hello};
	if (ft_thread_spawn(&rt_info, &t, &targ, FT_THREAD_STACKSIZE) == KO)
		ft_exit(1);
	while (x--)
		ft_print_stderr("Hello from main!\n");
	ft_thread_join(&t);
	ft_exit(0);
}
