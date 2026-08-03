/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "primitives.h"
# include "alloc.h"

/// \brief Owned, growable, always NUL-terminated byte string.
/// \note `size` excludes the terminating NUL; `capacity` is the allocated
/// byte count (including room for that NUL). `mem` is owned by whichever
/// allocator built the t_str and must be released with ft_str_destroy.
typedef struct s_str
{
	t_size	size;
	t_size	capacity;
	t_u8	*mem;
}	t_str;

/// \brief Allocates an empty, NUL-terminated t_str with room for `size` bytes.
/// \param allocator Allocator used for the backing buffer.
/// \param size Requested byte capacity (excluding the NUL); 0 is rejected.
/// \return New t_str with `.size == 0`, or a zeroed t_str (`.mem ==
/// nullptr`) if `size` is 0 or allocation fails.
t_str		ft_str(t_allocator allocator, t_size size);
/// \brief Frees a t_str's backing memory and zeroes it out.
/// \param allocator Allocator that owns `str->mem`; must match the one used
/// to build/grow it.
/// \param str String to release; safe to call again on the result (no-op
/// once `mem` is nullptr).
void		ft_str_destroy(t_allocator allocator, t_str *str)\
				__attribute__((__nonnull__(2)));
/// \brief Appends `n` bytes plus a NUL terminator, growing if needed.
/// \param allocator Allocator used to grow `str` via ft_str_reserve.
/// \param str Destination string; must already be initialized (non-null mem).
/// \param mem Borrowed source bytes; `n + 1` bytes are read (the extra byte
/// becomes the new terminator, so the caller's buffer must have one).
/// \param n Number of bytes to copy from `mem`.
/// \return OK, or KO if growing the buffer failed.
t_result	ft_str_extend(t_allocator allocator,\
				t_str *restrict const str,\
				const t_u8 *restrict const mem, t_size n)\
				__attribute__((__nonnull__(2, 3)));
/// \brief Grows a t_str's capacity by at least `n` bytes via realloc.
/// \param allocator Allocator that owns `str->mem`.
/// \param str String to grow; must already be initialized (non-null mem).
/// \param n Minimum extra capacity to add, in bytes.
/// \return OK, or KO if the realloc failed (str is left unchanged).
t_result	ft_str_reserve(t_allocator allocator,\
				t_str *restrict const str, t_size n)\
				__attribute__((__nonnull__(2)));
/// \brief Appends one byte, growing (doubling, or 4 bytes if empty) as needed.
/// \param allocator Allocator used to grow `str` when it runs out of room.
/// \param str Destination string; must already be initialized.
/// \param byte Byte to append; the string stays NUL-terminated afterward.
/// \return OK, or KO if growing the buffer failed.
t_result	ft_str_push_back(t_allocator allocator,\
				t_str *restrict const str, const t_u8 byte)\
				__attribute__((__nonnull__(2)));
/// \brief Removes the byte at index `i`, shifting the tail left by one.
/// \param v String to mutate in place.
/// \param i Index of the byte to remove.
/// \return OK, or KO if `v` is uninitialized or `i` is out of bounds
/// (`i >= v->size`).
t_result	ft_str_remove(t_str *restrict const v, t_size i)\
				__attribute__((__nonnull__(1)));

#endif
