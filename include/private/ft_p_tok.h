/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_tok.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:48:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/23 17:37:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_TOK_H
# define FT_P_TOK_H

# include "tokenizer.h"
# include "private/ft_p_bmi.h"

typedef int			(*t_8eater)(int);
typedef t_u16a		(*t_128eater)(t_vu128a);
typedef t_u32a		(*t_256eater)(t_vu256a);
typedef t_u64a		(*t_512eater)(t_vu512a);

typedef struct s_eaterset
{
	t_8eater	eater8;
	t_128eater	eater128;
	t_256eater	eater256;
	t_512eater	eater512;
}	t_eaterset;

t_token			ft_eat_while_u8(t_tokenizer *tk,\
					int (*fn)(int c))\
					__attribute__((pure, __nonnull__(1, 2)));
t_token			ft_eat_until_u8(t_tokenizer *tk,\
					int (*fn)(int c))\
					__attribute__((pure, __nonnull__(1, 2)));

t_token			ft_eat_while_u128(t_tokenizer *tk,\
					t_128eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			ft_eat_until_u128(t_tokenizer *tk,\
					t_128eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			ft_eat_while_u256(t_tokenizer *tk,\
					t_256eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			ft_eat_until_u256(t_tokenizer *tk,\
					t_256eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			ft_eat_while_u512(t_tokenizer *tk,\
					t_512eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_token			ft_eat_until_u512(t_tokenizer *tk,\
					t_512eater fn)\
					__attribute__((__nonnull__(1, 2)));

t_eaterset		get_eaterset(t_eater_select selection);

#endif
