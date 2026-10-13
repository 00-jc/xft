/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap.h                                         :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWISSMAP_H
# define SWISSMAP_H

# include "soa.h"

# ifndef SWISS_INITIAL_SIZE
#  define SWISS_INITIAL_SIZE	512
# endif

typedef struct s_swissmap
{
	t_soa		soa;
	t_size		count;
	t_size		tombstones;
}	t_swissmap;

t_swissmap	xft_new_swissmap_with(t_allocator allocator, t_size capacity);
t_swissmap	xft_new_swissmap(t_allocator allocator);
t_any		xft_swissmap_lookup(const t_swissmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((pure, __nonnull__(1)));
t_result	xft_swissmap_insert(t_allocator allocator,\
				t_swissmap *__restrict__ const map,\
				t_buffer key, t_u8 *__restrict__ const value)\
				__attribute__((__nonnull__(2, 4)));
void		xft_swissmap_destroy(t_allocator allocator,\
				t_swissmap *__restrict__ const map)\
				__attribute__((__nonnull__(2)));
void		xft_swissmap_delete(t_swissmap *__restrict__ const map,\
				t_buffer key)\
				__attribute__((__nonnull__(1)));
void		xft_swissmap_clear(t_swissmap *__restrict__ const map)\
				__attribute__((__nonnull__(1)));

#endif
