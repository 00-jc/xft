/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_indexmap_types.h                             :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_INDEXMAP_TYPES_H
# define XFT_P_INDEXMAP_TYPES_H

# include <xft/types/asm_types.h>

typedef enum e_imap_ctrl : t_u8
{
	IMAP_GROUP = XFT_NVEC_SIZE,
	IMAP_H2_MASK = 0x7F,
	IMAP_DELETED = 0x80,
	IMAP_EMPTY = 0xFF,
}	t_imap_ctrl;

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

#endif
