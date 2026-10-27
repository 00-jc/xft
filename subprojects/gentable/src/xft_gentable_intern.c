/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_intern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:15:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/gentable.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline static bool	gt__token(const t_gt_classes *__restrict__ const classes,
				t_gt_acc *__restrict__ const acc)
{
	t_u64	lsb;

	lsb = xft_tern(acc->open, 1, classes->idents & -classes->idents);
	acc->tok = (t_u32)xft_tern(acc->open, acc->tok,
			acc->base + xft_memctz_u64(lsb));
	acc->end = acc->base
		+ (t_u32)xft_memctz_u64(~(0ULL | classes->idents) & -lsb);
	acc->open = (acc->end == acc->base + sizeof(t_nvec)) & (lsb != 0);
	return (lsb != 0);
}

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline static t_gt_step	gt__codepoint(t_gt_classes *__restrict__ const classes,
				t_gt_acc *__restrict__ const acc)
{
	t_size	idx;
	t_u64	word;

	if (!gt__token(classes, acc))
		return (GT_STALL);
	acc->cp.start = acc->tok;
	idx = xft_tern(acc->tok + sizeof(t_u64) <= acc->src.size,
			acc->tok, acc->src.size - sizeof(t_u64));
	word = *(t_blk64r)(acc->src.mem + idx) >> ((acc->tok - idx) << 3);
	word = xft_hasz64(word ^ xft_populate('.'));
	acc->cp.type = (t_gt_entry_type)xft_tern((xft_memctz_u64(word) >> 3)
			< acc->end - acc->tok, RANGE, LITERAL);
	acc->state = (t_gt_state)xft_tern(acc->open, CODEPOINT, EXPCT_SEMI);
	return ((t_gt_step)xft_tern(acc->open, GT_STALL, GT_NEXT));
}

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__))
inline static t_gt_step	gt__expct_semi(t_gt_classes *__restrict__ const classes,
				t_gt_acc *__restrict__ const acc)
{
	const t_nmask	semi = classes->semicolon;
	const t_nmask	popped = semi ^ (semi - 1);

	classes->idents &= ~popped;
	classes->semicolon &= ~popped;
	acc->state = (t_gt_state)xft_tern(semi != 0, TAG, EXPCT_SEMI);
	return ((t_gt_step)xft_tern(!semi, GT_STALL, xft_tern(acc->base
				+ xft_memctz_u64(semi) < acc->end, GT_FAIL, GT_NEXT)));
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__, __hot__))
inline static t_gt_step	gt__tag(const t_gt_classes *__restrict__ const classes,
				t_vec *__restrict__ const vec,
				t_gt_acc *__restrict__ const acc)
{
	t_u32	tag;

	if (!gt__token(classes, acc))
		return (GT_STALL);
	tag = gt__tag_bits(acc);
	acc->state = (t_gt_state)xft_tern(acc->open, TAG, JMPLINE);
	acc->cp.type = (t_gt_entry_type)(acc->cp.type | tag);
	if (__builtin_expect(tag && !xft_vec_push_back(acc->allocator, vec,
				(const t_u8 *)&acc->cp, sizeof(t_gentable_entry)), 0))
		return (GT_FAIL);
	return ((t_gt_step)xft_tern(acc->open, GT_STALL, GT_NEXT));
}

__attribute__((__nonnull__(2, 3), __always_inline__, __used__, __hot__,
	__flatten__))
inline t_result	gt_classify_and_intern(t_gt_classes classes,
				t_vec *__restrict__ const vec,
				t_gt_acc *__restrict__ const acc)
{
	t_gt_step	step;

	classes.idents |= classes.digit;
	step = GT_NEXT;
	while (step == GT_NEXT)
	{
		if (acc->state == CODEPOINT)
			step = gt__codepoint(&classes, acc);
		else if (acc->state == EXPCT_SEMI)
			step = gt__expct_semi(&classes, acc);
		else if (acc->state == TAG)
			step = gt__tag(&classes, vec, acc);
		else
			step = gt__jmpline(acc);
	}
	return ((t_result)xft_tern(step == GT_FAIL, KO, OK));
}
