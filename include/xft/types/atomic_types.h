/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 01:16:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMIC_TYPES_H
# define ATOMIC_TYPES_H

# include <xft/primitives.h>

# define CLINE __GCC_CONSTRUCTIVE_SIZE

typedef volatile _Atomic(t_u8) __attribute__((__aligned__(CLINE)))	t_u8cl;
typedef volatile _Atomic(t_u16) __attribute__((__aligned__(CLINE)))	t_u16cl;
typedef volatile _Atomic(t_u32) __attribute__((__aligned__(CLINE)))	t_u32cl;
typedef volatile _Atomic(t_u64) __attribute__((__aligned__(CLINE)))	t_u64cl;
typedef volatile _Atomic(t_i8) __attribute__((__aligned__(CLINE)))	t_i8cl;
typedef volatile _Atomic(t_i16) __attribute__((__aligned__(CLINE)))	t_i16cl;
typedef volatile _Atomic(t_i32) __attribute__((__aligned__(CLINE)))	t_i32cl;
typedef volatile _Atomic(t_i64) __attribute__((__aligned__(CLINE)))	t_i64cl;

typedef volatile _Atomic(t_u32)										t_atomic32;
typedef volatile _Atomic(t_u64)										t_atomic64;
typedef volatile _Atomic(t_any)										t_atomicptr;
typedef t_atomic32													t_mutex;

# undef CLINE

# if defined(__x86_64__) || defined(__aarch64__) || defined(__powerpc64__)
#  define XFT_DESTRUCTIVE_ALIGN 128
# elif defined(__s390x__)
#  define XFT_DESTRUCTIVE_ALIGN 256
# elif defined(__arm__) || defined(__mips__) || defined(__hexagon__) \
	|| (defined(__sparc__) && !defined(__arch64__))
#  define XFT_DESTRUCTIVE_ALIGN 32
# elif defined(__m68k__)
#  define XFT_DESTRUCTIVE_ALIGN 16
# else
#  define XFT_DESTRUCTIVE_ALIGN 64
# endif

typedef struct s_ring_buffer
{
	t_atomicptr		*memory;
	t_size			alloc_bytes;
	t_u32a			size;

	_Alignas(XFT_DESTRUCTIVE_ALIGN)
	t_atomic32		head;
	_Alignas(XFT_DESTRUCTIVE_ALIGN)
	t_atomic32		tail;
}	t_ring_buffer;

typedef enum e_mutex_type : t_u8
{
	xft_lock_fast,
	xft_lock_slow,
	xft_lock_busy,
}	t_mutex_type;

typedef enum e_xft_lock_state : t_u8
{
	xft_unlocked = 0,
	xft_locked = 1,
	xft_contested = 2,
}	t_xft_lock_state;

typedef enum e_xft_atomic_ordering : t_i32
{
	xft_relaxed = __ATOMIC_RELAXED,
	xft_consume = __ATOMIC_CONSUME,
	xft_acquire = __ATOMIC_ACQUIRE,
	xft_release = __ATOMIC_RELEASE,
	xft_acq_rel = __ATOMIC_ACQ_REL,
	xft_seq_cst = __ATOMIC_SEQ_CST,
}	t_xft_atomic_ordering;

#endif
