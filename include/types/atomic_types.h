/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMIC_TYPES_H
# define ATOMIC_TYPES_H

# include "primitives.h"

typedef volatile uint8_t __attribute__((__aligned__(64)))		t_c_8;
typedef volatile uint16_t __attribute__((__aligned__(64)))		t_c_16;
typedef volatile uint32_t __attribute__((__aligned__(64)))		t_c_32;
typedef volatile uint64_t __attribute__((__aligned__(64)))		t_c_64;
typedef volatile int8_t __attribute__((__aligned__(64)))		t_c_i8;
typedef volatile int16_t __attribute__((__aligned__(64)))		t_c_i16;
typedef volatile int32_t __attribute__((__aligned__(64)))		t_c_i32;
typedef volatile int64_t __attribute__((__aligned__(64)))		t_c_i64;
typedef volatile t_c_i32										t_mutex_nonsh;
typedef volatile t_i32a											t_mutex;
typedef enum e_mutex_type
{
	FAST,
	SLOW,
	BUSY,
}	t_mutex_type;

# define XFT_UNLOCKED 0
# define XFT_LOCKED 1
# define XFT_CONTESTED 2

#endif
