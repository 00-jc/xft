/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_allocator_types.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:33:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORT_ALLOCATOR_TYPES_H
# define REPORT_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_reporta
{
	void		*slab;
	t_size		slabsize;
	void		*bmp;
	void		*free[GPA_CLASSES];
	t_size		n_allocs;
	t_size		n_frees;
	t_size		slabs;
	t_size		reuses;
	t_size		misses;
	t_size		free_depth[GPA_CLASSES];
	t_size		paged;
	t_f64		avg_frag;
	t_u8		buffer[1024];
}	t_reporta;

#endif
