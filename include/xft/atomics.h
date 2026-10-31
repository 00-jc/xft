/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 01:25:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_H
# define ATOMICS_H

# include <xft/primitives.h>
# include <xft/types/atomic_types.h>
# include <xft/alloc.h>

# ifndef XFT_MUTEX_SPIN
#  define XFT_MUTEX_SPIN 32
# endif

void			xft_thread_fence(t_xft_atomic_ordering memorder);
void			xft_signal_fence(t_xft_atomic_ordering memorder);
void			xft_backoff(t_u64 n);

void			xft_futex_wait(t_atomic32 *__restrict__ const atomic,
					t_u32a value_to_wait)\
					__attribute__((__nonnull__(1)));

void			xft_futex_wake(t_atomic32 *__restrict__ const atomic,
					t_u32a waiters)\
					__attribute__((__nonnull__(1)));

void			xft_wait_for_signal(t_atomic32 *__restrict__ const atomic)\
					__attribute__((__nonnull__(1)));

void			xft_send_signal(t_atomic32 *__restrict__ const atomic)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_lock(t_mutex *__restrict__ const mutex,\
					const t_mutex_type type)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_unlock(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

void			xft_mutex_init(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

t_ring_buffer	xft_new_ring_buffer(t_allocator allocator, t_u32a min_size);

void			xft_destroy_ring_buffer(t_allocator allocator,\
					t_ring_buffer *__restrict__ const rb)\
					__attribute__((__nonnull__(2)));

t_result		xft_ring_buffer_submit(t_ring_buffer *__restrict__ const rb,\
					t_any ptr)\
					__attribute__((__nonnull__(1)));

t_any			xft_ring_buffer_steal(t_ring_buffer *__restrict__ const rb)\
					__attribute__((__nonnull__(1)));

#endif
