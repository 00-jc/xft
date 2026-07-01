/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 15:06:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 18:08:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FMT_H
# define FMT_H

# include "io.h"
# include "primitives.h"

//	%x -> hex lower (u64 / whole value slot) 
//	%X -> hex upper (u64 / whole value slot)
//	%p -> hex lower (u64 / whole value slot)
//	%b -> u8
//	%y -> i8
//	%w -> u16
//	%o -> i16
//	%u -> u32
//	%d -> i32
//	%q -> u64
//	%i -> i64
//	%e -> u128 (ptr)
//	%m -> i128 (ptr)
//	%s -> string (ptr)
//	%f -> double (reinterpret cast from value)

t_result	ft_fmt_writer(t_writer *writer, t_buffer fmt, t_u64 *values)\
				__attribute__((__nonnull__(1, 3)));

#endif
