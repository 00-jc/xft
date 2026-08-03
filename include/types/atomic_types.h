/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:24:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 17:53:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMIC_TYPES_H
# define ATOMIC_TYPES_H

# include "primitives.h"

/*
 *	aligned to a cache line so they do not produce false sharing
 */

/// \brief Cache-line-aligned, `volatile`-qualified scalar types for use as
///        atomic operands (`__atomic_*` builtins / `ft_thread_fence` et al).
///        Each variant only differs in the underlying scalar type; the
///        `volatile` prevents the compiler from caching the value across
///        atomic ops and the 64-byte alignment keeps each instance on its
///        own cache line to avoid false sharing between cores.
typedef volatile uint8_t __attribute__((__aligned__(64)))		t_c_8;
typedef volatile uint16_t __attribute__((__aligned__(64)))		t_c_16;
typedef volatile uint32_t __attribute__((__aligned__(64)))		t_c_32;
typedef volatile uint64_t __attribute__((__aligned__(64)))		t_c_64;
typedef volatile __uint128_t __attribute__((__aligned__(64)))	t_c_128;
typedef volatile int8_t __attribute__((__aligned__(64)))		t_c_i8;
typedef volatile int16_t __attribute__((__aligned__(64)))		t_c_i16;
typedef volatile int32_t __attribute__((__aligned__(64)))		t_c_i32;
typedef volatile int64_t __attribute__((__aligned__(64)))		t_c_i64;
typedef volatile __int128_t __attribute__((__aligned__(64)))	t_c_i128;
typedef volatile float __attribute__((__aligned__(64)))			t_c_f32;
typedef volatile double __attribute__((__aligned__(64)))		t_c_f64;
typedef volatile long double __attribute__((__aligned__(64)))	t_c_f80;
typedef volatile uintptr_t __attribute__((__aligned__(64)))		t_c_ptr;
typedef volatile void * __attribute__((__aligned__(64)))		t_c_any;
/// \brief Cache-aligned `t_c_i32`, currently unused by any mutex code in
///        this tree; reserved for a non-process-shared mutex variant.
typedef t_c_i32													t_mutex_nonsh;
/// \brief The mutex word type: a plain (non-cache-aligned) `t_i32a` used
///        as the futex-word for `ft_mutex_lock`/`ft_mutex_unlock`. Valid
///        states are `FT_UNLOCKED`, `FT_LOCKED` and `FT_CONTESTED`.
typedef volatile t_i32a											t_mutex;

/// \brief Contention strategy selector consumed by `ft_mutex_lock`; only
///        affects behavior once the lock-free fast path fails.
typedef enum e_mutex_type
{
	FAST,	///< Bounded spin (`FT_MUTEX_SPIN` iters) then futex wait.
	SLOW,	///< Futex wait immediately on first contention, no spinning.
	BUSY,	///< Spin with backoff indefinitely; never sleeps in a futex.
}	t_mutex_type;

/// \brief Mutex word states: no holder.
# define FT_UNLOCKED 0
/// \brief Mutex word states: held, no waiters known to be parked.
# define FT_LOCKED 1
/// \brief Mutex word states: held and at least one waiter may be parked
///        in `futex(FUTEX_WAIT)`; `ft_mutex_unlock` must wake on this state.
# define FT_CONTESTED 2

/// \brief Linux `futex(2)` operation codes. Only `FUTEX_WAIT` and
///        `FUTEX_WAKE` are currently issued (by `ft_futex_wait` /
///        `ft_futex_wake`); the rest are reserved for future use.
# define FUTEX_WAIT               0
# define FUTEX_WAKE               1
# define FUTEX_REQUEUE            3
# define FUTEX_CMP_REQUEUE        4
# define FUTEX_WAKE_OP            5
# define FUTEX_LOCK_PI            6
# define FUTEX_UNLOCK_PI          7
# define FUTEX_TRYLOCK_PI         8
# define FUTEX_WAIT_BITSET        9
# define FUTEX_WAKE_BITSET       10
# define FUTEX_WAIT_REQUEUE_PI   11
# define FUTEX_CMP_REQUEUE_PI    12
# define FUTEX_LOCK_PI2          13

#endif
