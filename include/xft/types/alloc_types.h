/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_TYPES_H
# define ALLOC_TYPES_H

# include <xft/alloc/page_alloc.h>
# include <xft/alloc/arena_alloc.h>

typedef enum e_gpa_conf : t_u32
{
	GPA_CLASSES = 14,
	GPA_SLABSIZE = 131072,
}	t_gpa_conf;

typedef enum e_reporta_conf : t_u16
{
	REPORTA_BUFFER = 1024,
}	t_reporta_conf;

typedef struct s_gpa
{
	t_any	slab;
	t_size	slabsize;
	t_any	bmp;
	t_any	free[GPA_CLASSES];
}	t_gpa;

typedef struct s_reporta
{
	t_any		slab;
	t_size		slabsize;
	t_any		bmp;
	t_any		free[GPA_CLASSES];
	t_size		n_allocs;
	t_size		n_frees;
	t_size		slabs;
	t_size		reuses;
	t_size		misses;
	t_size		free_depth[GPA_CLASSES];
	t_size		paged;
	t_f64		avg_frag;
	t_u8		buffer[REPORTA_BUFFER];
}	t_reporta;

#endif
