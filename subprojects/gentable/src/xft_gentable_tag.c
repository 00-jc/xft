/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_tag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:15:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/gentable.h>

// head is bytes [0, 8) and tail [len - 8, len) of the tag; anything that is
// not 9 or 12 bytes long reads the zero block instead and matches nothing
__attribute__((__nonnull__(1), __hot__, __pure__))
t_u32	gt__tag_bits(const t_gt_acc *__restrict__ const acc)
{
	const t_u64a	zero[2] = {0, 0};
	const t_u32		len = acc->end - acc->tok;
	const t_u8		*word;
	t_u64			head;
	t_u64			tail;

	word = (const t_u8 *)xft_tern(!acc->open && (len == 9 || len == 12),
			(t_u64a)(acc->src.mem + acc->tok), (t_u64a)zero);
	head = *(t_blk64r)word;
	tail = *(t_blk64r)(word + xft_tern(len == 12, 4, 1));
	return ((t_u32)(xft_tern((head == GT_XID_STAR) & (tail == GT_ID_START),
			START, 0) | xft_tern((head == GT_XID_CONT)
			& (tail == GT_CONTINUE), CONTINUE, 0)));
}
