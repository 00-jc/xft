/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_u8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:10:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/05 13:17:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tok.h"

__attribute__((__nonnull__(1, 2)))
t_token	ft_eat_while_u8(t_tokenizer *tk,
	int (*fn)(int c))
{
	t_u8	*lexeme;
	size_t	init;
	size_t	len;
	size_t	i;

	lexeme = tk->mem + tk->cc;
	i = tk->cc;
	init = tk->cc;
	while (i < tk->max && fn(tk->mem[i]))
		++i;
	len = i - init;
	tk->cc += len;
	return ((t_token){
		.mem = lexeme,
		.len = len,
	});
}

__attribute__((__nonnull__(1, 2)))
t_token	ft_eat_until_u8(t_tokenizer *tk,
	int (*fn)(int c))
{
	t_u8	*lexeme;
	size_t	init;
	size_t	len;
	size_t	i;

	lexeme = tk->mem + tk->cc;
	i = tk->cc;
	init = tk->cc;
	while (i < tk->max && !fn(tk->mem[i]))
		++i;
	len = i - init;
	tk->cc += len;
	return ((t_token){
		.mem = lexeme,
		.len = len,
	});
}
