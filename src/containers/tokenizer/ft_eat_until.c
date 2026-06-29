/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_until.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:08:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:46:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tok.h"

#if FT_HAS_512_VEC

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_until(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu512a))
		return (ft_eat_until_u512(tk, set.eater512));
	else if (remaining >= sizeof(t_vu256a))
		return (ft_eat_until_u256(tk, set.eater256));
	else if (remaining >= sizeof(t_vu128a))
		return (ft_eat_until_u128(tk, set.eater128));
	else
		return (ft_eat_until_u8(tk, set.eater8));
}

#elif FT_HAS_256_VEC

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_until(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu256a))
		return (ft_eat_until_u256(tk, set.eater256));
	else if (remaining >= sizeof(t_vu128a))
		return (ft_eat_until_u128(tk, set.eater128));
	else
		return (ft_eat_until_u8(tk, set.eater8));
}

#else

__attribute__((__nonnull__(1), __noinline__, __used__))
t_token	ft_eat_until(t_tokenizer *tk, t_eater_select select)
{
	t_eaterset	set;
	t_size		remaining;

	set = get_eaterset(select);
	remaining = tk->max - tk->cc;
	if (remaining >= sizeof(t_vu128a))
		return (ft_eat_until_u128(tk, set.eater128));
	else
		return (ft_eat_until_u8(tk, set.eater8));
}

#endif
