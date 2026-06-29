/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:36:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:26:13 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include <stdint.h>
# include <stddef.h>
# include <limits.h>

typedef uint8_t __attribute__((__may_alias__))							t_u8;
typedef int8_t __attribute__((__may_alias__))							t_i8;

typedef uint16_t __attribute__((__may_alias__, __aligned__(1)))			t_u16;
typedef uint16_t __attribute__((__may_alias__, __aligned__(2)))			t_u16a;
typedef int16_t __attribute__((__may_alias__, __aligned__(1)))			t_i16;
typedef int16_t __attribute__((__may_alias__, __aligned__(2)))			t_i16a;

typedef uint32_t __attribute__((__may_alias__, __aligned__(1)))			t_u32;
typedef uint32_t __attribute__((__may_alias__, __aligned__(4)))			t_u32a;
typedef int32_t __attribute__((__may_alias__, __aligned__(1)))			t_i32;
typedef int32_t __attribute__((__may_alias__, __aligned__(4)))			t_i32a;

typedef uint64_t __attribute__((__may_alias__, __aligned__(1)))			t_u64;
typedef uint64_t __attribute__((__may_alias__, __aligned__(8)))			t_u64a;
typedef int64_t __attribute__((__may_alias__, __aligned__(1)))			t_i64;
typedef int64_t __attribute__((__may_alias__, __aligned__(8)))			t_i64a;

typedef __uint128_t __attribute__((__may_alias__, __aligned__(1)))		t_u128;
typedef __uint128_t __attribute__((__may_alias__, __aligned__(16)))		t_u128a;
typedef __int128_t __attribute__((__may_alias__, __aligned__(1)))		t_i128;
typedef __int128_t __attribute__((__may_alias__, __aligned__(16)))		t_i128a;

typedef float __attribute__((__may_alias__, __aligned__(1)))			t_f32;
typedef float __attribute__((__may_alias__, __aligned__(4)))			t_f32a;

typedef double __attribute__((__may_alias__, __aligned__(1)))			t_f64;
typedef double __attribute__((__may_alias__, __aligned__(8)))			t_f64a;

typedef long double __attribute__((__may_alias__, __aligned__(1)))		t_f80;
typedef long double __attribute__((__may_alias__, __aligned__(8)))		t_f80a;

typedef uintptr_t __attribute__((__may_alias__))						t_uptr;

typedef t_u64															t_size;
typedef t_i64															t_ssize;

# ifdef __clang__

typedef struct s_buffer
{
	t_size										size;
	t_u8 __attribute__	((counted_by(size)))	*mem;
}	t_buffer;

# else

typedef struct s_buffer
{
	t_size		size;
	t_u8		*mem;
}	t_buffer;

# endif

typedef enum e_result
{
	OK = 1,
	KO = 0,
}	t_result;

typedef struct s_span
{
	t_size	typesize;
	t_size	n;
}	t_span;

#endif
