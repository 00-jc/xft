/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_tok_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_TOK_TYPES_H
# define FT_P_TOK_TYPES_H

# include "types/ft_p_asm_primitives.h"

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

#endif
