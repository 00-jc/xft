/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_atomics.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ATOMICS_H
# define XFT_P_ATOMICS_H

# include "types/atomic_types.h"

void			xft_mutex_backoff(t_u64 n);

void			xft_mutex_spin(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_busy(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_slow(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

#endif
