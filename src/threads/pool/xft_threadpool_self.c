/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_self.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 13:56:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:56:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>

__attribute__((__returns_nonnull__))
t_tp_self	*xft__self(void)
{
	static _Thread_local t_tp_self	self;

	return (&self);
}
