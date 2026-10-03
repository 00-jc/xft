/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator_types.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_TYPES_H
# define GENERAL_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_gpa
{
	t_any	slab;
	t_size	slabsize;
	t_any	bmp;
	t_any	free[GPA_CLASSES];
}	t_gpa;

#endif
