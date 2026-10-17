/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_jmpline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:15:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gentable.h"

__attribute__((__nonnull__(1), __hot__))
t_gt_step	gt__jmpline(t_gt_acc *__restrict__ const acc)
{
	const t_u8	*nl;

	nl = xft_memchr(acc->src.mem + acc->end, '\n', acc->src.size - acc->end);
	acc->next = (t_u32)xft_tern(nl != nullptr,
			(t_u64a)nl - (t_u64a)acc->src.mem + 1, acc->src.size);
	acc->state = CODEPOINT;
	return (GT_STALL);
}
