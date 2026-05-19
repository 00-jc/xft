/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:57:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/06 02:08:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "mem.h"
# include "ctype.h"

typedef struct s_tokenizer
{
	t_u8	*mem;
	size_t	max;
	size_t	cc;
}	t_tokenizer;

typedef struct s_token
{
	t_u8	*mem;
	size_t	len;
}	t_token;

typedef enum e_eater_select
{
	set_blank = 0,
	set_alpha = 1,
	set_digit = 2,
	set_xdigit = 3,
}	t_eater_select;

t_token		ft_eat_while(t_tokenizer *tk, t_eater_select select)\
				__attribute__((__nonnull__(1), __noinline__, __used__));
t_token		ft_eat_until(t_tokenizer *tk, t_eater_select select)\
				__attribute__((__nonnull__(1), __noinline__, __used__));
t_u32a		ft_tokenizer_goto(t_tokenizer *tk, t_u8 byte)\
				__attribute__((__nonnull__(1)));
void		ft_skip_whitespace(t_tokenizer *tk)\
				__attribute__((__nonnull__(1)));
t_tokenizer	ft_tokenizer_over(void *mem, size_t size)\
				__attribute__((__nonnull__(1), const));
t_u32a		ft_match_next(t_tokenizer *tk, t_u8 expected)\
				__attribute__((__nonnull__(1)));
#endif
