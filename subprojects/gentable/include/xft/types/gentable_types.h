/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gentable_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:34:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENTABLE_TYPES_H
# define GENTABLE_TYPES_H

# include <xft/xft.h>

// tags compared as two overlapping LE u64s, bytes [0, 8) and [len - 8, len)
// "XID_Star", "ID_Start" of XID_Start, "XID_Cont", "Continue" of XID_Continue

typedef enum e_gt_tag : t_u64
{
	GT_XID_STAR = 0x726174535F444958,
	GT_ID_START = 0x74726174535F4449,
	GT_XID_CONT = 0x746E6F435F444958,
	GT_CONTINUE = 0x65756E69746E6F43,
}	t_gt_tag;

typedef enum e_carry_idx
{
	OPEN_IDENT = 0,
	OPEN_NUMERAL = 1,
	OPEN_DIGIT = 2,
	OPEN_COMMENT = 3,
}	t_carry_idx;

typedef t_u8		t_carry;

typedef enum e_gt_state
{
	LINEST,
	CODEPOINT,
	EXPCT_SEMI,
	TAG,
	JMPLINE,
}	t_gt_state;

typedef struct s_gentable_state
{
	t_gpa					gpa;
	t_allocator				allocator;
	t_vec					set;
	t_buffer				database;
}	t_gentable_state;

// OR'd: shape in the low bits, tag in the high ones, START | RANGE = 0x8001

typedef enum e_gt_entry_type
{
	LITERAL = 0,
	RANGE = 1,
	CONTINUE = 0x4000,
	START = 0x8000,
}	t_gt_entry_type;

typedef struct s_gentable_entry
{
	t_gt_entry_type		type;
	t_u32				start;
}	t_gentable_entry;

typedef struct s_gt_table
{
	const char			*name;
	t_u64				len;
	t_gt_entry_type		tag;
}	t_gt_table;

typedef enum e_gt_step
{
	GT_FAIL,
	GT_NEXT,
	GT_STALL,
}	t_gt_step;

typedef struct s_gt_acc
{
	t_allocator			allocator;
	t_buffer			src;
	t_gentable_entry	cp;
	t_u32				base;
	t_u32				tok;
	t_u32				next;
	t_u32				end;
	t_gt_state			state;
	bool				open;
}	t_gt_acc;

typedef struct s_gt_classes
{
	t_nmask		digit;
	t_nmask		idents;
	t_nmask		hash;
	t_nmask		newline;
	t_nmask		semicolon;
}	t_gt_classes;

#endif
