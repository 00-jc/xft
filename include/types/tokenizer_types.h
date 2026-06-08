/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_TYPES_H
# define TOKENIZER_TYPES_H

# include "primitives.h"

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

#endif
