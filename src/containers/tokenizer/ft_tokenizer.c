/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 02:08:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

__attribute__((__nonnull__(1), const, __always_inline__))
inline t_tokenizer	ft_tokenizer_over(void *mem, size_t size)
{
	return ((t_tokenizer){
		.mem = mem,
		.cc = 0,
		.max = size,
	});
}

__attribute__((__nonnull__(1)))
t_u32a	ft_tokenizer_goto(t_tokenizer *tk, t_u8 byte)
{
	void	*bptr;
	size_t	newcc;

	bptr = ft_memchr(tk->mem + tk->cc, byte, tk->max - tk->cc);
	if (!bptr)
		return (0);
	newcc = (t_uptr)bptr - (t_uptr)tk->mem;
	tk->cc = newcc;
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_skip_whitespace(t_tokenizer *tk)
{
	(void)ft_eat_while(tk, set_blank);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_u32a	ft_match_next(t_tokenizer *tk, t_u8 expected)
{
	if (tk->cc + 1 > tk->max || tk->mem[tk->cc] != expected)
		return (0);
	++tk->cc;
	return (1);
}
