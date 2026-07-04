/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:22:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 18:17:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_H
# define ATOMICS_H

# include "primitives.h"
# include "types/atomic_types.h"

# ifndef FT_MUTEX_SPIN
#  define FT_MUTEX_SPIN 64
# endif

void			ft_thread_fence(t_i32a memorder);
void			ft_signal_fence(t_i32a memorder);

void			ft_mutex_lock(t_mutex *__restrict__ const mutex,\
					const t_mutex_type type)\
					__attribute__((__nonnull__(1)));

void			ft_mutex_unlock(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			ft_mutex_init(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

#endif
