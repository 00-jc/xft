/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:24:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 22:25:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMICS_H
# define ATOMICS_H

# include "primitives.h"

typedef _Atomic t_u8		t_au8;
typedef _Atomic t_i8		t_ai8;

typedef _Atomic t_u16a		t_au16;
typedef _Atomic t_i16a		t_ai16;

typedef _Atomic t_u32a		t_au32;
typedef _Atomic t_i32a		t_ai32;

typedef _Atomic t_u64a		t_au64;
typedef _Atomic t_i64a		t_ai64;

typedef _Atomic t_u128a		t_au128;
typedef _Atomic t_i128a		t_ai128;

typedef _Atomic t_f32a		t_af32;
typedef _Atomic t_f64a		t_af64;
typedef _Atomic t_f80a		t_af80;

typedef _Atomic t_uptr		t_auptr;

typedef t_au64				t_asize;
typedef t_ai64				t_assize;

#endif
