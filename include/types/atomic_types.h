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
typedef t_c_i32													t_mutex_nonsh;
typedef volatile t_i32a											t_mutex;

typedef enum e_mutex_type
{
	FAST,
	SLOW,
	BUSY,
}	t_mutex_type;

# define FT_UNLOCKED 0
# define FT_LOCKED 1
# define FT_CONTESTED 2

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
