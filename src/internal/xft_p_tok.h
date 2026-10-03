/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_TOK_H
# define XFT_P_TOK_H

# include "tokenizer.h"

t_token			xft_eat_while_u8(t_tokenizer *tk,\
					int (*fn)(int c))\
					__attribute__((pure, __nonnull__(1, 2)));
t_token			xft_eat_until_u8(t_tokenizer *tk,\
					int (*fn)(int c))\
					__attribute__((pure, __nonnull__(1, 2)));

t_token			xft_eat_while_u128(t_tokenizer *tk,\
					t_128eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			xft_eat_until_u128(t_tokenizer *tk,\
					t_128eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			xft_eat_while_u256(t_tokenizer *tk,\
					t_256eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			xft_eat_until_u256(t_tokenizer *tk,\
					t_256eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			xft_eat_while_u512(t_tokenizer *tk,\
					t_512eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			xft_eat_until_u512(t_tokenizer *tk,\
					t_512eater fn)\
					__attribute__((__nonnull__(1, 2)));

#endif
