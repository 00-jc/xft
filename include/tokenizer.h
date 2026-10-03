/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "mem.h"
# include "ctype.h"
# include "xft_p_bmi.h"

typedef struct s_tokenizer
{
	t_u8	*mem;
	t_size	max;
	t_size	cc;
}	t_tokenizer;

typedef struct s_token
{
	t_u8	*mem;
	t_size	len;
}	t_token;

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

t_token		xft_eat_while(t_tokenizer *tk, const t_eaterset *set)\
				__attribute__((__nonnull__(1, 2), __noinline__, __used__));
t_token		xft_eat_until(t_tokenizer *tk, const t_eaterset *set)\
				__attribute__((__nonnull__(1, 2), __noinline__, __used__));
t_u32a		xft_tokenizer_goto(t_tokenizer *tk, t_u8 byte)\
				__attribute__((__nonnull__(1)));
void		xft_skip_whitespace(t_tokenizer *tk)\
				__attribute__((__nonnull__(1)));
t_tokenizer	xft_new_tokenizer(t_any mem, t_size size)\
				__attribute__((__nonnull__(1), const));
t_u32a		xft_match_next(t_tokenizer *tk, t_u8 expected)\
				__attribute__((__nonnull__(1)));
#endif
