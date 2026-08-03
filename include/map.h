/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vec.h"
# include "hash.h"
# include "private/ft_p_asm.h"

/// \brief Default table_size (in buckets) used by ft_map_new.
/// \note Must be a multiple of 16 (one SSE group); ft_map_with rejects any
/// capacity that fails `capacity & 15`.
# ifndef MAP_INITIAL_SIZE
#  define MAP_INITIAL_SIZE	512
# endif

/// \brief Mask for the 7-bit H2 hash fragment stored per bucket in `meta`.
/// \note Derived as `(hash >> 57) & MAP_H2_MASK`, i.e. the top 7 bits of the
/// 64-bit hash; kept small enough that bit 7 stays free for the
/// empty/deleted markers below.
# define MAP_H2_MASK		0x7F
/// \brief Meta-byte marker: bucket held an entry that was deleted (tombstone).
/// \note Probing must keep scanning past a MAP_DELETED slot; only a
/// MAP_EMPTY slot terminates a probe.
# define MAP_DELETED 		0x80
/// \brief Meta-byte marker: bucket has never held an entry (probe stop).
# define MAP_EMPTY			0xFF

/// \name Indices into the internal `t_size data[3..4]` scratch arrays passed
/// between the swiss-table probing helpers (H2 fragment, block count,
/// current group, and — for lookup/delete — the key length).
/// @{
# define H2		0
# define NBLK	1
# define GROUP	2
# define SIZE	3
/// @}

# ifdef __clang__

typedef struct s_bucket
{
	t_size										key_len;
	t_u8 __attribute__	((counted_by(key_len)))	*key;
	t_u8										*value;
}	t_bucket;

typedef struct s_map
{
	t_size												table_size;
	t_size												count;
	t_bucket __attribute__	((counted_by(table_size)))	*buckets;
	t_u8												*meta;
	t_buffer											bucket_buf;
	t_buffer											meta_buf;
}	t_map;

# else

typedef struct s_bucket
{
	t_size		key_len;
	t_u8		*key;
	t_u8		*value;
}	t_bucket;

typedef struct s_map
{
	t_size		table_size;
	t_size		count;
	t_bucket	*buckets;
	t_u8		*meta;
	t_buffer	bucket_buf;
	t_buffer	meta_buf;
}	t_map;

# endif

t_map		ft_map_with(t_allocator allocator, t_size capacity);
t_map		ft_map_new(t_allocator allocator);
t_any		ft_map_lookup(const t_map *__restrict__ const map, t_buffer key)\
				__attribute__((__nonnull__(1)));
t_result	ft_map_insert(t_allocator allocator,\
				t_map *__restrict__ const map,\
				t_buffer key, t_u8 *__restrict__ const value)\
				__attribute__((__nonnull__(2, 4)));
void		ft_map_destroy(t_allocator allocator,\
				t_map *__restrict__ const map)\
				__attribute__((__nonnull__(2)));
void		ft_map_delete(t_map *__restrict__ const map, t_buffer key)\
				__attribute__((__nonnull__(1)));
void		ft_map_clear(t_map *map)\
				__attribute__((__nonnull__(1)));

#endif
