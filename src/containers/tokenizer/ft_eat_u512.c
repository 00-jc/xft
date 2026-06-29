/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_u512.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:10:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:51:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tok.h"

#if FT_HAS_512_VEC

__attribute__((__nonnull__(1, 2)))
static inline t_token	ft_eat_while_u512_tail(t_tokenizer *tk,
	t_512eater fn, t_size i)
{
	t_token	exit;
	t_size	finaloffst;
	t_size	remaining;
	t_u64a	mask;

	remaining = tk->max - i;
	mask = ~fn(*((t_blk512r)((tk->mem + i + remaining)
					- sizeof(t_vu512a))));
	mask &= 0xFFFFFFFFFFFFFFFF << (sizeof(t_vu512a) - remaining);
	if (mask)
	{
		finaloffst = ft_memctz_u64(mask)
			- (sizeof(t_vu512a) - remaining);
		exit.len = (i + finaloffst) - tk->cc;
		exit.mem = tk->mem + tk->cc;
		tk->cc = i + finaloffst;
		return (exit);
	}
	exit.mem = tk->mem + tk->cc;
	exit.len = tk->max - tk->cc;
	tk->cc = tk->max;
	return (exit);
}

__attribute__((__nonnull__(1, 2)))
t_token	ft_eat_while_u512(t_tokenizer *tk,
	t_512eater fn)
{
	t_u64a		msk;
	t_u8		*mem;
	t_token		exit;
	t_size		finaloffst;
	t_size		i;

	i = tk->cc;
	mem = tk->mem;
	while (i + sizeof(t_vu512a) <= tk->max)
	{
		msk = ~fn(*((t_blk512r)(mem + i)));
		if (msk)
		{
			finaloffst = ft_memctz_u64(msk);
			exit.len = (i + finaloffst) - tk->cc;
			exit.mem = mem + tk->cc;
			tk->cc = i + finaloffst;
			return (exit);
		}
		i += sizeof(t_vu512a);
	}
	if (i == tk->max)
		return ((void)(exit = (t_token){.mem = mem + tk->cc
			, .len = i - tk->cc}), (void)(tk->cc = tk->max), exit);
	return (ft_eat_while_u512_tail(tk, fn, i));
}

__attribute__((__nonnull__(1, 2)))
static inline t_token	ft_eat_until_u512_tail(t_tokenizer *tk,
	t_512eater fn, t_size i)
{
	t_token	exit;
	t_size	finaloffst;
	t_size	remaining;
	t_u64a	mask;

	remaining = tk->max - i;
	mask = fn(*((t_blk512r)((tk->mem + i + remaining)
					- sizeof(t_vu512a))));
	mask &= 0xFFFFFFFFFFFFFFFF << (sizeof(t_vu512a) - remaining);
	if (mask)
	{
		finaloffst = ft_memctz_u64(mask)
			- (sizeof(t_vu512a) - remaining);
		exit.len = (i + finaloffst) - tk->cc;
		exit.mem = tk->mem + tk->cc;
		tk->cc = i + finaloffst;
		return (exit);
	}
	exit.mem = tk->mem + tk->cc;
	exit.len = tk->max - tk->cc;
	tk->cc = tk->max;
	return (exit);
}

__attribute__((__nonnull__(1, 2)))
t_token	ft_eat_until_u512(t_tokenizer *tk,
	t_512eater fn)
{
	t_u64a		msk;
	t_u8		*mem;
	t_token		exit;
	t_size		finaloffst;
	t_size		i;

	i = tk->cc;
	mem = tk->mem;
	while (i + sizeof(t_vu512a) <= tk->max)
	{
		msk = fn(*((t_blk512r)(mem + i)));
		if (msk)
		{
			finaloffst = ft_memctz_u64(msk);
			exit.len = (i + finaloffst) - tk->cc;
			exit.mem = mem + tk->cc;
			tk->cc = i + finaloffst;
			return (exit);
		}
		i += sizeof(t_vu512a);
	}
	if (i == tk->max)
		return ((void)(exit = (t_token){.mem = mem + tk->cc
			, .len = i - tk->cc}), (void)(tk->cc = tk->max), exit);
	return (ft_eat_until_u512_tail(tk, fn, i));
}

#endif
