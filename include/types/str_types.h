/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_TYPES_H
# define STR_TYPES_H

# include "primitives.h"

typedef struct s_str
{
	size_t	size;
	size_t	capacity;
	t_u8	*mem;
}	t_str;

#endif
