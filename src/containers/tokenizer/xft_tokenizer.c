/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_tok.h"

__attribute__((__nonnull__(1), const, __always_inline__, __used__))
inline t_tokenizer	xft_new_tokenizer(t_any mem, t_size size)
{
	return ((t_tokenizer){
		.mem = mem,
		.cc = 0,
		.max = size,
	});
}

__attribute__((__nonnull__(1)))
t_u32a	xft_tokenizer_goto(t_tokenizer *tk, t_u8 byte)
{
	t_any	bptr;
	t_size	newcc;

	bptr = xft_memchr(tk->mem + tk->cc, byte, tk->max - tk->cc);
	if (!bptr)
		return (0);
	newcc = (t_uptr)bptr - (t_uptr)tk->mem;
	tk->cc = newcc;
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_skip_whitespace(t_tokenizer *tk)
{
	const t_eaterset	set = {.eater8 = xft_isspace};

	(void)xft_eat_while(tk, &set);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_u32a	xft_match_next(t_tokenizer *tk, t_u8 expected)
{
	if (tk->cc + 1 > tk->max || tk->mem[tk->cc] != expected)
		return (0);
	++tk->cc;
	return (1);
}
