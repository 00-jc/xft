/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 02:33:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/20 15:49:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_MAP_H
# define FT_P_MAP_H

# include "map.h"

void		ft_map_insert_unchecked(t_map *__restrict__ const map,\
				t_buffer key, t_u8 *__restrict__ const value)\
				__attribute__((__nonnull__(1, 3)));

t_result	ft_map_rehash(t_allocator allocator,\
				t_map *__restrict__ const map)\
				__attribute__((__nonnull__(2)));

size_t		ft__map_lookup_offset(const t_map *__restrict__ const map,\
				const t_u8 *__restrict__ const mem, size_t data[4])\
				__attribute__((__nonnull__(1, 2, 3)));

#endif
