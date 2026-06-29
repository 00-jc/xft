/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TYPES_H
# define MAP_TYPES_H

# include "primitives.h"

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

#endif
