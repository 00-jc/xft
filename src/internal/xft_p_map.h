/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_MAP_H
# define XFT_P_MAP_H

# include "map.h"

void		xft_map_insert_unchecked(t_map *__restrict__ const map,\
				t_buffer key, t_u8 *__restrict__ const value)\
				__attribute__((__nonnull__(1, 3)));

t_result	xft_map_rehash(t_allocator allocator,\
				t_map *__restrict__ const map)\
				__attribute__((__nonnull__(2)));

t_size		xft__map_lookup_offset(const t_map *__restrict__ const map,\
				const t_u8 *__restrict__ const mem, t_size data[4])\
				__attribute__((__nonnull__(1, 2, 3)));

#endif
