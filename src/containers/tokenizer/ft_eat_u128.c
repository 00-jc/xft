/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_u128.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:10:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 14:52:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tok.h"

__attribute__((__nonnull__(1, 2)))
static inline t_token	ft_eat_while_u128_tail(t_tokenizer *tk,
	t_128eater fn, size_t i)
{
	t_token	exit;
	size_t	finaloffst;
	size_t	remaining;
	t_u16a	mask;

	remaining = tk->max - i;
	mask = (t_u16a) ~ fn(*((t_blk128r)((tk->mem + i + remaining)
					- sizeof(t_vu128a))));
	mask &= 0xFFFF << (sizeof(t_vu128a) - remaining);
	if (mask)
	{
		finaloffst = ft_memctz_u16(mask)
			- (sizeof(t_vu128a) - remaining);
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
t_token	ft_eat_while_u128(t_tokenizer *tk,
	t_128eater fn)
{
	t_u16a		msk;
	t_u8		*mem;
	t_token		exit;
	size_t		finaloffst;
	size_t		i;

	i = tk->cc;
	mem = tk->mem;
	while (i + sizeof(t_vu128a) <= tk->max)
	{
		msk = (t_u16a) ~ fn(*((t_blk128r)(mem + i)));
		if (msk)
		{
			finaloffst = ft_memctz_u16(msk);
			exit.len = (i + finaloffst) - tk->cc;
			exit.mem = mem + tk->cc;
			tk->cc = i + finaloffst;
			return (exit);
		}
		i += sizeof(t_vu128a);
	}
	if (i == tk->max)
		return ((void)(exit = (t_token){.mem = mem + tk->cc
			, .len = i - tk->cc}), (void)(tk->cc = tk->max), exit);
	return (ft_eat_while_u128_tail(tk, fn, i));
}

__attribute__((__nonnull__(1, 2)))
static inline t_token	ft_eat_until_u128_tail(t_tokenizer *tk,
	t_128eater fn, size_t i)
{
	t_token	exit;
	size_t	finaloffst;
	size_t	remaining;
	t_u16a	mask;

	remaining = tk->max - i;
	mask = fn(*((t_blk128r)((tk->mem + i + remaining)
					- sizeof(t_vu128a))));
	mask &= 0xFFFF << (sizeof(t_vu128a) - remaining);
	if (mask)
	{
		finaloffst = ft_memctz_u16(mask)
			- (sizeof(t_vu128a) - remaining);
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
t_token	ft_eat_until_u128(t_tokenizer *tk,
	t_128eater fn)
{
	t_u16a		msk;
	t_u8		*mem;
	t_token		exit;
	size_t		finaloffst;
	size_t		i;

	i = tk->cc;
	mem = tk->mem;
	while (i + sizeof(t_vu128a) <= tk->max)
	{
		msk = fn(*((t_blk128r)(mem + i)));
		if (msk)
		{
			finaloffst = ft_memctz_u16(msk);
			exit.len = (i + finaloffst) - tk->cc;
			exit.mem = mem + tk->cc;
			tk->cc = i + finaloffst;
			return (exit);
		}
		i += sizeof(t_vu128a);
	}
	if (i == tk->max)
		return ((void)(exit = (t_token){.mem = mem + tk->cc
			, .len = i - tk->cc}), (void)(tk->cc = tk->max), exit);
	return (ft_eat_until_u128_tail(tk, fn, i));
}
