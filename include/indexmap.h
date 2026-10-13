/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   indexmap.h                                         :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXMAP_H
# define INDEXMAP_H

# include "soa.h"

# ifndef INDEXMAP_INITIAL_SIZE
#  define INDEXMAP_INITIAL_SIZE	512
# endif

# define INDEXMAP_NPOS			__SIZE_MAX__

typedef struct s_indexmap
{
	t_soa		soa;
	t_size		count;
	t_size		tombstones;
}	t_indexmap;

t_indexmap	xft_new_indexmap_with(t_allocator allocator, t_size capacity);
t_indexmap	xft_new_indexmap(t_allocator allocator);
t_size		xft_indexmap_lookup(const t_indexmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((pure, __nonnull__(1)));
t_result	xft_indexmap_insert(t_allocator allocator,\
				t_indexmap *__restrict__ const map,\
				t_buffer key, t_size value)\
				__attribute__((__nonnull__(2)));
void		xft_indexmap_destroy(t_allocator allocator,\
				t_indexmap *__restrict__ const map)\
				__attribute__((__nonnull__(2)));
t_size		xft_indexmap_delete(t_indexmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((__nonnull__(1)));
void		xft_indexmap_clear(t_indexmap *__restrict__ const map)\
				__attribute__((__nonnull__(1)));

#endif
