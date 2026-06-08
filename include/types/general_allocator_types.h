/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_allocator_types.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_ALLOCATOR_TYPES_H
# define GENERAL_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_gpa
{
	void	*slab;
	size_t	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
}	t_gpa;

#endif
