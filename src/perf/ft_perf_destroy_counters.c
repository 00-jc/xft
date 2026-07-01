/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_destroy_counters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_perf.h"

__attribute__((__nonnull__(1)))
void	ft_perf_destroy_counters(t_perf_counters c)
{
	t_size	i;

	i = 0;
	while (i < HW_COUNTERS_N + SW_COUNTERS_N)
		ft_close((int)c[i++]);
}
