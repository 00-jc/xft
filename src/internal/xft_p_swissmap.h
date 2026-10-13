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

# include "swissmap.h"
# include "hash.h"
# include "mem.h"
# include "bmi.h"
# include "xft_p_asm.h"

# define SWISS_GROUP		16
# define SWISS_H2_MASK		0x7F
# define SWISS_DELETED		0x80
# define SWISS_EMPTY		0xFF
# define SWISS_NPOS			__SIZE_MAX__

typedef enum e_swiss_field
{
	SWISS_META,
	SWISS_KEY,
	SWISS_VALUE,
	SWISS_FIELDS,
}	t_swiss_field;

typedef struct s_swiss_slot
{
	t_buffer	key;
	t_u8		*value;
	t_u8		meta;
}	t_swiss_slot;

typedef struct s_swiss_probe
{
	t_size		nblks;
	t_size		group;
	t_u8		h2;
}	t_swiss_probe;

const t_soa_context	*xft__swiss_ctx(void)\
						__attribute__((const, __returns_nonnull__));

#endif
