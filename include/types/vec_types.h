/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TYPES_H
# define VEC_TYPES_H

# include "primitives.h"

typedef struct s_vec
{
	size_t		size;
	t_buffer	buf;
}	t_vec;

#endif
