/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_destroy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:57:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:51:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>

__attribute__((__nonnull__(2), __flatten__))
void	xft_threadpool_destroy(t_allocator allocator,
	t_threadpool *__restrict__ const tp)
{
	xft__stop_threads(allocator, tp, tp->n_workers, xft_tp_drain);
	xft__free_rings(allocator, tp, tp->n_workers);
	tp->n_workers = 0;
}
