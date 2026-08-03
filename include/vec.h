/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:17:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "mem.h"
# include "alloc.h"
# include "types/vec_types.h"
# include <stddef.h>

/// \brief Allocates a t_vec with room for `size` elements of `type_size`
/// bytes each.
/// \param allocator Allocator used for the backing buffer.
/// \param size Initial element capacity.
/// \param type_size Size of one element, in bytes.
/// \return New empty t_vec, or a zeroed t_vec (`.buf.mem == nullptr`) if
/// `size * type_size` is 0, overflows, or allocation fails.
t_vec			ft_vec(t_allocator allocator, t_size size, t_size type_size);
/// \brief Frees a t_vec's backing buffer and zeroes it out.
/// \param allocator Allocator that owns `v->buf`; must match the one used
/// to build/grow it.
/// \param v Vec to release. Only releases the buffer itself; elements that
/// own their own memory (e.g. sub-buffers) are not freed — use
/// ft_vec_pop_managed/ft_vec_remove_managed while draining first if needed.
void			ft_vec_destroy(t_allocator allocator, t_vec *v)\
					__attribute__((__nonnull__(2)));

/// \brief Element count currently stored.
/// \param v Vec to inspect.
/// \param type_size Size of one element, in bytes.
/// \return `v->size / type_size`.
/// \note `v->size` is a byte count, not an element count — always go
/// through this (or divide by `type_size` yourself) rather than reading
/// `v->size` directly as a length.
t_size			ft_vec_len(const t_vec *__restrict__ const v, t_size type_size)\
					__attribute__((__nonnull__(1), pure));

/// \brief Appends one element, growing (doubling, or 4 bytes if empty) as
/// needed.
/// \param allocator Allocator used to grow `vec` when it runs out of room.
/// \param vec Destination vec.
/// \param data Borrowed source of one element (`type_size` bytes); copied in.
/// \param type_size Size of one element, in bytes.
/// \return OK, or KO if growing the buffer failed.
t_result		ft_vec_push_back(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					const t_u8 *__restrict__ const data, t_size type_size)\
					__attribute__((__nonnull__(2, 3)));

/// \brief Read-only pointer to the element at `idx`.
/// \param vec Vec to index into.
/// \param idx Element index.
/// \param type_size Size of one element, in bytes.
/// \return Pointer into `vec`'s buffer, or nullptr if `idx` is out of
/// bounds (branchless: computed via a mask, not a conditional).
t_cany			ft_vec_get(const t_vec *__restrict__ const vec, t_size idx,
					t_size type_size) __attribute__((__nonnull__(1),
						pure));

/// \brief Mutable pointer to the element at `idx`.
/// \param vec Vec to index into.
/// \param idx Element index.
/// \param type_size Size of one element, in bytes.
/// \return Pointer into `vec`'s buffer, or nullptr if `idx` is out of
/// bounds (branchless: computed via a mask, not a conditional).
t_any			ft_vec_get_mut(const t_vec *__restrict__ const vec, t_size idx,
					t_size type_size) __attribute__((__nonnull__(1),
						pure));

/// \brief Mutable pointer to the last element.
/// \param vec Vec to inspect.
/// \param type_size Size of one element, in bytes.
/// \return Pointer to the last element, or nullptr if `vec` is empty.
t_any			ft_vec_get_last(const t_vec *__restrict__ const vec,\
					t_size type_size)\
					__attribute__((__nonnull__(1), pure));

/// \brief Read-only pointer to the last element.
/// \param vec Vec to inspect.
/// \param type_size Size of one element, in bytes.
/// \return Pointer to the last element, or nullptr if `vec` is empty.
t_cany			ft_vec_peek_last(const t_vec *__restrict__ const vec,\
					t_size type_size) __attribute__((__nonnull__(1), pure));

/// \brief Grows a t_vec's byte capacity by at least `n` bytes via realloc.
/// \param allocator Allocator that owns `vec->buf`.
/// \param vec Vec to grow.
/// \param n Minimum extra capacity to add, in bytes (not elements).
/// \return OK, or KO if the realloc failed (vec is left unchanged).
t_result		ft_vec_reserve(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					t_size n)\
					__attribute__((__nonnull__(2)));

/// \brief Appends a run of raw bytes, growing if needed.
/// \param allocator Allocator used to grow `vec` via ft_vec_reserve.
/// \param vec Destination vec; must already be initialized (non-null buf).
/// \param data Borrowed bytes to copy in; `data.size` need not be a
/// multiple of any element size (this is a raw byte append).
/// \return OK, or KO if growing the buffer failed.
t_result		ft_vec_extend(t_allocator allocator,\
					t_vec *__restrict__ const vec,\
					t_buffer data)\
					__attribute__((__nonnull__(2)));

/// \brief Drops the last element by shrinking `size`; does not free
/// anything the element itself owns.
/// \param v Vec to shrink; a no-op if already empty.
/// \param type_size Size of one element, in bytes.
void			ft_vec_pop(t_vec *__restrict__ const v, t_size type_size)\
					__attribute__((__nonnull__(1)));

/// \brief Pops the last element, copying it out to `dest` first.
/// \param v Vec to pop from; must already be initialized (non-null buf).
/// \param dest Owned destination for the copied-out element (`type_size`
/// bytes).
/// \param type_size Size of one element, in bytes.
/// \return OK, or KO if `v` was empty (nothing copied, nothing popped).
t_result		ft_vec_popmv(t_vec *__restrict__ const v, t_any const dest,
					t_size type_size) __attribute__((__nonnull__(1)));

/// \brief Pops the last element and frees it via `allocator`.
/// \param allocator Allocator used to free the popped element.
/// \param v Vec to pop from; must already be initialized (non-null buf).
/// \param type_size Size of one element, in bytes.
/// \return OK, or KO if `v` was empty.
/// \note The element is reinterpreted as a t_buffer and passed to
/// `allocator.vtable.free` — only use this when the vec's element type
/// *is* (or starts with) a t_buffer that owns its own memory.
t_result		ft_vec_pop_managed(t_allocator allocator,\
					t_vec *restrict const v, size_t type_size)\
					__attribute__((__always_inline__, __nonnull__(2)));

/// \brief Removes the element at index `i`, shifting later elements down
/// (order-preserving), without freeing anything the element owns.
/// \param v Vec to mutate in place.
/// \param i Index of the element to remove.
/// \param type_size Size of one element, in bytes.
/// \return OK, or KO if `v` is empty or `i` is out of bounds.
t_result		ft_vec_remove(t_vec *__restrict__ const v, t_size i,\
					t_size type_size) __attribute__((__nonnull__(1)));

/// \brief Removes the element at index `i` and frees it via `allocator`
/// before shifting later elements down.
/// \param allocator Allocator used to free the removed element.
/// \param v Vec to mutate in place.
/// \param i Index of the element to remove.
/// \param type_size Size of one element, in bytes.
/// \return OK, or KO if `v` is empty or `i` is out of bounds.
/// \note Same t_buffer-reinterpretation caveat as ft_vec_pop_managed.
t_result		ft_vec_remove_managed(t_allocator allocator,\
					t_vec *restrict const v, size_t i, size_t type_size)\
					__attribute__((__nonnull__(2)));

/// \brief Resets element count to 0 without freeing the backing buffer or
/// any memory owned by individual elements.
/// \param v Vec to clear.
void			ft_vec_clear(t_vec *__restrict__ const v)\
					__attribute__((__nonnull__(1)));

#endif
