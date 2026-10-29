/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 13:43:41 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_TYPES_H
# define ALLOC_TYPES_H

# include <xft/alloc/page_alloc.h>
# include <xft/alloc/arena_alloc.h>
# include <xft/types/atomic_types.h>

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

typedef struct s_ts_gpa
{
	t_mutex		mutex;
	t_gpa		gpa;
}	t_ts_gpa;

typedef struct s_ts_arena
{
	t_mutex		mutex;
	t_arena		arena;
}	t_ts_arena;

typedef struct s_ts_reporta
{
	t_mutex		mutex;
	t_reporta	reporta;
}	t_ts_reporta;

#endif
