/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_async.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ASYNC_H
# define XFT_P_ASYNC_H

# include <xft/async.h>

void		blocking_async(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

void		blocking_await(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

void		threaded_async(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

void		threaded_await(t_async *self, t_task *task)\
			__attribute__((__nonnull__(1, 2)));

#endif
