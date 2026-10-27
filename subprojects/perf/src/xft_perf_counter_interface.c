/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_counter_interface.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_perf.h>
#include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1), __always_inline__))
inline void	xft_perf_counters_start(t_perf_counters c)
{
	xft_ioctl((int)c[0], xft_perf_event_ioc_enable, xft_perf_ioc_flag_group);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	xft_perf_counters_stop(t_perf_counters c)
{
	xft_ioctl((int)c[0], xft_perf_event_ioc_disable, xft_perf_ioc_flag_group);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	xft_perf_counters_reset(t_perf_counters c)
{
	xft_ioctl((int)c[0], xft_perf_event_ioc_reset, xft_perf_ioc_flag_group);
}
