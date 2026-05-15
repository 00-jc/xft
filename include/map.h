/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:35:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 04:09:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vec.h"
# include "hash.h"
# include "private/ft_p_asm.h"

# ifndef MAP_INITIAL_SIZE
#  define MAP_INITIAL_SIZE	512
# endif

# define MAP_H2_MASK		0x7F
# define MAP_DELETED 		0x80
# define MAP_EMPTY			0xFF

# define H2		0
# define NBLK	1
# define GROUP	2
# define SIZE	3

# ifdef __clang__

typedef struct s_bucket
{
	size_t										key_len;
	t_u8 __attribute__	((counted_by(key_len)))	*key;
	t_u8										*value;
}	t_bucket;

typedef struct s_map
{
	size_t												table_size;
	size_t												count;
	t_bucket __attribute__	((counted_by(table_size)))	*buckets;
	t_u8												*meta;
	t_buffer											bucket_buf;
	t_buffer											meta_buf;
}	t_map;

# else

typedef struct s_bucket
{
	size_t		key_len;
	t_u8		*key;
	t_u8		*value;
}	t_bucket;

typedef struct s_map
{
	size_t		table_size;
	size_t		count;
	t_bucket	*buckets;
	t_u8		*meta;
	t_buffer	bucket_buf;
	t_buffer	meta_buf;
}	t_map;

# endif

t_map		ft_map_with(size_t capacity);
t_map		ft_map_new(void);
void		*ft_map_lookup(const t_map *__restrict__ const map,
				t_u8 *__restrict__ const mem, size_t size)\
				__attribute__((__nonnull__(1, 2)));
t_u32a		ft_map_insert(t_map	*__restrict__ const map,
				t_u8 *__restrict__ const key,
				size_t keylen,
				t_u8 *__restrict__ const value)\
				__attribute__((__nonnull__(1, 2, 4)));
void		ft_map_destroy(t_map *__restrict__ const map)\
				__attribute__((__nonnull__(1)));
void		ft_map_delete(t_map	*__restrict__ const map,
				t_u8 *__restrict__ const key, size_t keylen)\
				__attribute__((__nonnull__(1, 2)));
void		ft_map_clear(t_map *map)\
				__attribute__((__nonnull__(1)));

#endif
