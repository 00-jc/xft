/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:36:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/20 15:25:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include <stdint.h>

typedef uint8_t __attribute__((__may_alias__))							t_u8;

typedef uint16_t __attribute__((__may_alias__, __aligned__(1)))			t_u16;
typedef uint16_t __attribute__((__may_alias__, __aligned__(2)))			t_u16a;

typedef uint32_t __attribute__((__may_alias__, __aligned__(1)))			t_u32;
typedef uint32_t __attribute__((__may_alias__, __aligned__(4)))			t_u32a;

typedef uint64_t __attribute__((__may_alias__, __aligned__(1)))			t_u64;
typedef uint64_t __attribute__((__may_alias__, __aligned__(8)))			t_u64a;

typedef __uint128_t __attribute__((__may_alias__, __aligned__(1)))		t_u128;
typedef __uint128_t __attribute__((__may_alias__, __aligned__(16)))		t_u128a;

typedef float __attribute__((__may_alias__, __aligned__(1)))			t_f32;
typedef float __attribute__((__may_alias__, __aligned__(4)))			t_f32a;

typedef double __attribute__((__may_alias__, __aligned__(1)))			t_f64;
typedef double __attribute__((__may_alias__, __aligned__(8)))			t_f64a;

typedef long double __attribute__((__may_alias__, __aligned__(1)))		t_f80;
typedef long double __attribute__((__may_alias__, __aligned__(8)))		t_f80a;

typedef uintptr_t __attribute__((__may_alias__))						t_uptr;

# ifdef __clang__

typedef struct s_buffer
{
	size_t										size;
	t_u8 __attribute__	((counted_by(size)))	*mem;
}	t_buffer;

# else

typedef struct s_buffer
{
	size_t		size;
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
	size_t	typesize;
	size_t	n;
}	t_span;

#endif
