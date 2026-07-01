/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_counter_interface.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_perf.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_perf_counters_start(t_perf_counters c)
{
	ft_ioctl((int)c[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_perf_counters_stop(t_perf_counters c)
{
	ft_ioctl((int)c[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_perf_counters_reset(t_perf_counters c)
{
	ft_ioctl((int)c[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
}
