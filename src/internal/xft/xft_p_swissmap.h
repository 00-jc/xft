/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_swissmap.h                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SWISSMAP_H
# define XFT_P_SWISSMAP_H

# include <xft/swissmap.h>
# include <xft/hash.h>
# include <xft/types/xft_p_swissmap_types.h>

const t_soa_context	*xft__swiss_ctx(void)\
						__attribute__((const, __returns_nonnull__));
t_anycl				xft__swiss_meta(const t_swissmap *__restrict__ const map)\
						__attribute__((pure, __nonnull__(1),\
							__returns_nonnull__));
void				xft__swiss_set(t_swissmap *__restrict__ const map,\
						t_size idx, t_swiss_slot slot)\
						__attribute__((__nonnull__(1)));
t_swiss_slot		xft__swiss_get(const t_swissmap *__restrict__ const map,\
						t_size idx)\
						__attribute__((pure, __nonnull__(1)));
t_swiss_probe		xft__swiss_probe(const t_swissmap *__restrict__ const map,\
						t_buffer key)\
						__attribute__((pure, __nonnull__(1)));
t_size				xft__swiss_find(const t_swissmap *__restrict__ const map,\
						t_buffer key, t_swiss_probe probe)\
						__attribute__((pure, __nonnull__(1)));
t_size				xft__swiss_find_free(\
						const t_swissmap *__restrict__ const map,\
						t_swiss_probe probe)\
						__attribute__((pure, __nonnull__(1)));

#endif
