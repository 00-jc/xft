/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:22:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 22:35:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_H
# define ATOMICS_H

# include "primitives.h"
# include "types/atomic_types.h"

/// \brief Bounded spin count used by `ft_mutex_lock(FAST)` before it
///        falls back to a futex wait; overridable by defining it earlier.
# ifndef FT_MUTEX_SPIN
#  define FT_MUTEX_SPIN 32
# endif

/// \brief Emits a full compiler+CPU memory fence (`__atomic_thread_fence`).
/// \param memorder A `__ATOMIC_*` memory order constant (e.g.
///        `__ATOMIC_ACQUIRE`, `__ATOMIC_RELEASE`, `__ATOMIC_SEQ_CST`).
void			ft_thread_fence(t_i32a memorder);
/// \brief Emits a compiler-only fence against reordering with signal
///        handlers (`__atomic_signal_fence`); no CPU instruction is issued.
/// \param memorder A `__ATOMIC_*` memory order constant.
void			ft_signal_fence(t_i32a memorder);

/// \brief Acquires `mutex`, blocking until it succeeds.
/// \param mutex Pointer to a mutex word previously set up by
///        `ft_mutex_init`. Must not be null.
/// \param type Contention strategy used only when the uncontended fast-path
///        CAS fails:
///        - `FAST`: spins up to `FT_MUTEX_SPIN` times with exponential
///          backoff, then falls back to a `futex(FUTEX_WAIT)` loop.
///        - `BUSY`: spins with exponential backoff indefinitely and never
///          sleeps in a futex; only worth it for very short critical
///          sections with reliably low contention.
///        - `SLOW`: skips spinning and blocks on `futex(FUTEX_WAIT)`
///          immediately on the first contended attempt.
/// \note On the uncontended path this does a single acquire-CAS from
///       `FT_UNLOCKED` to locked and returns; `type` only matters once
///       another holder is already present.
void			ft_mutex_lock(t_mutex *__restrict__ const mutex,\
					const t_mutex_type type)\
					__attribute__((__nonnull__(1)));

/// \brief Releases `mutex` acquired via `ft_mutex_lock`.
/// \param mutex Pointer to the locked mutex word. Must not be null.
/// \note Release-decrements the word; if it was `FT_CONTESTED` (i.e. a
///       waiter may be parked in a futex), it is reset to `FT_UNLOCKED`
///       and `futex(FUTEX_WAKE)` is issued to release one waiter. Calling
///       this on a mutex that is not held is undefined.
void			ft_mutex_unlock(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

/// \brief Initializes `mutex` to the unlocked state (`FT_UNLOCKED`).
/// \param mutex Pointer to the mutex word to initialize. Must not be null.
void			ft_mutex_init(t_mutex *__restrict__ const mutex)\
					__attribute__((__nonnull__(1)));

#endif
