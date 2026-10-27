/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gentable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:34:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENTABLE_H
# define GENTABLE_H

# include <xft/types/gentable_types.h>

# define GT_XID_PATH		"src/xid/xft_xidtable.c"
# define GT_HEADER_FMT		"\nconst t_u32\t\tg_xid_%s[][2] = {\n"
# define GT_ENTRY_FMT		"{0x%s, 0x%s},\n"
# define GT_EPILOGUE_FMT	"};\n\nconst t_size\tg_xid_%s_len = %q;\n"

t_result			gt_iterate(t_allocator allocator, t_buffer src,
						t_vec *__restrict__ const vec)\
						__attribute__((__nonnull__(3)));
t_gt_classes		gt_classify(t_nvec wide,
						t_carry *__restrict__ const carry)\
						__attribute__((__nonnull__(2)));
t_result			gt_classify_and_intern(t_gt_classes classes,
						t_vec *__restrict__ const vec,
						t_gt_acc *__restrict__ const acc)\
						__attribute__((__nonnull__(2, 3)));
t_result			gt_emit(t_buffer src, const t_vec *__restrict__ const set,
						const char *__restrict__ const path)\
						__attribute__((__nonnull__(2, 3)));
t_gt_step			gt__jmpline(t_gt_acc *__restrict__ const acc)\
						__attribute__((__nonnull__(1)));
t_u32				gt__tag_bits(const t_gt_acc *__restrict__ const acc)\
						__attribute__((__nonnull__(1), __pure__));

#endif
