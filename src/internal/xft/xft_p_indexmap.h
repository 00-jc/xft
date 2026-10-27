/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_indexmap.h                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_INDEXMAP_H
# define XFT_P_INDEXMAP_H

# include <xft/indexmap.h>
# include <xft/hash.h>
# include <xft/types/xft_p_indexmap_types.h>

const t_soa_context	*xft__imap_ctx(void)\
						__attribute__((const, __returns_nonnull__));
t_u8				*xft__imap_meta(const t_indexmap *__restrict__ const map)\
						__attribute__((pure, __nonnull__(1),\
							__returns_nonnull__));
void				xft__imap_set(t_indexmap *__restrict__ const map,\
						t_size idx, t_imap_slot slot)\
						__attribute__((__nonnull__(1)));
t_imap_slot			xft__imap_get(const t_indexmap *__restrict__ const map,\
						t_size idx)\
						__attribute__((pure, __nonnull__(1)));
t_imap_probe		xft__imap_probe(const t_indexmap *__restrict__ const map,\
						t_buffer key)\
						__attribute__((pure, __nonnull__(1)));
t_imap_probe		xft__imap_probe_seeded(\
						const t_indexmap *__restrict__ const map,\
						t_buffer key, t_u64a seed)\
						__attribute__((pure, __nonnull__(1)));
t_size				xft__imap_find(const t_indexmap *__restrict__ const map,\
						t_buffer key, t_imap_probe probe)\
						__attribute__((pure, __nonnull__(1)));
t_size				xft__imap_find_free(\
						const t_indexmap *__restrict__ const map,\
						t_imap_probe probe)\
						__attribute__((pure, __nonnull__(1)));

#endif
