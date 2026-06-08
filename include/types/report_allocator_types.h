/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_allocator_types.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORT_ALLOCATOR_TYPES_H
# define REPORT_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_reporta
{
	void	*slab;
	size_t	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
	size_t	n_allocs;
	size_t	n_frees;
	size_t	slabs;
	size_t	reuses;
	size_t	misses;
	size_t	free_depth[GPA_CLASSES];
	size_t	paged;
	t_f64	avg_frag;
}	t_reporta;

#endif
