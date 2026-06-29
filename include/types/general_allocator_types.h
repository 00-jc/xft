/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator_types.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_TYPES_H
# define GENERAL_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_gpa
{
	void	*slab;
	t_size	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
}	t_gpa;

#endif
