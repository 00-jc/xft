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

# include "indexmap.h"
# include "hash.h"
# include "mem.h"
# include "bmi.h"
# include "xft_p_asm.h"

# define IMAP_GROUP			XFT_NVEC_SIZE
# define IMAP_H2_MASK		0x7F
# define IMAP_DELETED		0x80
# define IMAP_EMPTY			0xFF

typedef enum e_imap_field
{
	IMAP_META,
	IMAP_KEY,
	IMAP_VALUE,
	IMAP_SEED,
	IMAP_FIELDS,
}	t_imap_field;

typedef struct s_imap_slot
{
	t_buffer	key;
	t_size		value;
	t_u64a		seed;
	t_u8		meta;
}	t_imap_slot;

typedef struct s_imap_probe
{
	t_size		nblks;
	t_size		group;
	t_u64a		seed;
	t_u8		h2;
}	t_imap_probe;

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
