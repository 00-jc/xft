/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
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
