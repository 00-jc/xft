/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_eat_while.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_tok.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1, 2), __noinline__, __used__))
t_token	xft_eat_while(t_tokenizer *tk, const t_eaterset *set)
{
	t_size	remaining;

	remaining = tk->max - tk->cc;
	if (set->eater512 && remaining >= sizeof(t_vu512))
		return (xft_eat_while_u512(tk, set->eater512));
	else if (set->eater256 && remaining >= sizeof(t_vu256))
		return (xft_eat_while_u256(tk, set->eater256));
	else if (set->eater128 && remaining >= sizeof(t_vu128))
		return (xft_eat_while_u128(tk, set->eater128));
	else
		return (xft_eat_while_u8(tk, set->eater8));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1, 2), __noinline__, __used__))
t_token	xft_eat_while(t_tokenizer *tk, const t_eaterset *set)
{
	t_size	remaining;

	remaining = tk->max - tk->cc;
	if (set->eater256 && remaining >= sizeof(t_vu256))
		return (xft_eat_while_u256(tk, set->eater256));
	else if (set->eater128 && remaining >= sizeof(t_vu128))
		return (xft_eat_while_u128(tk, set->eater128));
	else
		return (xft_eat_while_u8(tk, set->eater8));
}

#else

__attribute__((__nonnull__(1, 2), __noinline__, __used__))
t_token	xft_eat_while(t_tokenizer *tk, const t_eaterset *set)
{
	t_size	remaining;

	remaining = tk->max - tk->cc;
	if (set->eater128 && remaining >= sizeof(t_vu128))
		return (xft_eat_while_u128(tk, set->eater128));
	else
		return (xft_eat_while_u8(tk, set->eater8));
}

#endif
