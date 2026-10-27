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

# include <xft/types/indexmap_types.h>

t_indexmap	xft_new_indexmap_with(t_allocator allocator, t_size capacity);
t_indexmap	xft_new_indexmap(t_allocator allocator);
t_size		xft_indexmap_lookup(const t_indexmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((pure, __nonnull__(1)));
t_size		xft_indexmap_lookup_seeded(\
				const t_indexmap *__restrict__ const map,\
				t_imap_key key)\
				__attribute__((pure, __nonnull__(1)));
t_result	xft_indexmap_insert(t_allocator allocator,\
				t_indexmap *__restrict__ const map,\
				t_buffer key, t_size value)\
				__attribute__((__nonnull__(2)));
t_result	xft_indexmap_insert_seeded(t_allocator allocator,\
				t_indexmap *__restrict__ const map,\
				t_imap_key key, t_size value)\
				__attribute__((__nonnull__(2)));
void		xft_indexmap_destroy(t_allocator allocator,\
				t_indexmap *__restrict__ const map)\
				__attribute__((__nonnull__(2)));
t_size		xft_indexmap_delete(t_indexmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((__nonnull__(1)));
t_size		xft_indexmap_delete_seeded(t_indexmap *__restrict__ const map,\
				t_imap_key key)\
				__attribute__((__nonnull__(1)));
void		xft_indexmap_clear(t_indexmap *__restrict__ const map)\
				__attribute__((__nonnull__(1)));
void		xft_indexmap_iterate(t_indexmap *__restrict__ const map,
				t_imap_iter_callback f)\
				__attribute__((__nonnull__(1)));
t_u8		*xft_indexmap_meta(const t_indexmap *__restrict__ const indexmap)\
				__attribute__((pure, __returns_nonnull__, __nonnull__(1)));
t_u64a		*xft_indexmap_seed(const t_indexmap *__restrict__ const indexmap)\
				__attribute__((pure, __returns_nonnull__, __nonnull__(1)));

#endif
