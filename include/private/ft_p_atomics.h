/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_atomics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_ATOMICS_H
# define FT_P_ATOMICS_H

# include "types/atomic_types.h"

void			ft_mutex_backoff(t_u64 n);

void			ft_mutex_spin(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			ft_mutex_busy(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			ft_mutex_slow(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

#endif
