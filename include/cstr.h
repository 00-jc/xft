/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTR_H
# define CSTR_H

# include "str.h"

/// \brief Length of a NUL-terminated C string, in bytes (NUL excluded).
/// \param str Borrowed, NUL-terminated buffer; not modified.
/// \return Byte count before the terminating NUL.
/// \note SIMD scan (512/256/128-bit, selected at compile time via
/// FT_HAS_*_VEC) that reads in vector-width strides after aligning to the
/// first stride boundary; the trailing partial group is masked off rather
/// than read past `str`'s allocation.
t_size			ft_strlen(const char *__restrict__ str)\
					__attribute__((__nonnull__(1)));

/// \brief Builds an owned, NUL-terminated t_str by copying a C string.
/// \param allocator Allocator used for the new t_str's backing memory.
/// \param cstr Borrowed, NUL-terminated source; copied, not retained.
/// \return New t_str holding a copy of `cstr`, or a zeroed t_str
/// (`.mem == nullptr`) on allocation failure.
t_str			ft_cstr_to_str(t_allocator allocator, const char *cstr)\
					__attribute__((__nonnull__(2)));

#endif
