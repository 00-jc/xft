/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_swissmap_types.h                             :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SWISSMAP_TYPES_H
# define XFT_P_SWISSMAP_TYPES_H

# include <xft/types/asm_types.h>

typedef enum e_swiss_ctrl : t_u8
{
	SWISS_GROUP = XFT_NVEC_SIZE,
	SWISS_H2_MASK = 0x7F,
	SWISS_DELETED = 0x80,
	SWISS_EMPTY = 0xFF,
}	t_swiss_ctrl;

typedef enum e_swiss_npos : t_u64
{
	SWISS_NPOS = __SIZE_MAX__,
}	t_swiss_npos;

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

#endif
