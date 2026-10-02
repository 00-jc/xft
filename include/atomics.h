/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:22:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/07 21:30:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_H
# define ATOMICS_H

# include "primitives.h"
# include "types/atomic_types.h"

# ifndef XFT_MUTEX_SPIN
#  define XFT_MUTEX_SPIN 32
# endif

void			xft_thread_fence(t_i32a memorder);
void			xft_signal_fence(t_i32a memorder);

void			xft_mutex_lock(t_mutex *__restrict__ const mutex,\
					const t_mutex_type type)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_unlock(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_init(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

#endif
