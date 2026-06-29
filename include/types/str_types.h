/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_TYPES_H
# define STR_TYPES_H

# include "primitives.h"

typedef struct s_str
{
	t_size	size;
	t_size	capacity;
	t_u8	*mem;
}	t_str;

#endif
