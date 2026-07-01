/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_while.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tok.h"

#if FT_HAS_512_VEC

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_while(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu512))
		return (ft_eat_while_u512(tk, set.eater512));
	else if (remaining >= sizeof(t_vu256))
		return (ft_eat_while_u256(tk, set.eater256));
	else if (remaining >= sizeof(t_vu128))
		return (ft_eat_while_u128(tk, set.eater128));
	else
		return (ft_eat_while_u8(tk, set.eater8));
}

#elif FT_HAS_256_VEC

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_while(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu256))
		return (ft_eat_while_u256(tk, set.eater256));
	else if (remaining >= sizeof(t_vu128))
		return (ft_eat_while_u128(tk, set.eater128));
	else
		return (ft_eat_while_u8(tk, set.eater8));
}

#else

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_while(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu128))
		return (ft_eat_while_u128(tk, set.eater128));
	else
		return (ft_eat_while_u8(tk, set.eater8));
}

#endif
