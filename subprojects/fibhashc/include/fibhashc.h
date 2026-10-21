/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fibhashc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:15:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 23:12:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIBHASHC_H
# define FIBHASHC_H

# include "xft.h"

typedef struct s_src_span
{
	t_u32a	start;
	t_u32a	len;
}	t_src_span;

typedef struct s_fhc_cursor
{
	const t_u8	*pos;
	const t_u8	*run;
	t_u8		open_run;
}	t_fhc_cursor;

t_vec		fhc_run_pipeline(t_allocator allocator, t_buffer src);
t_u64		fhc_load_span(const t_u8 *__restrict__ const p, t_u32 len)\
				__attribute__((__nonnull__(1), __pure__));

t_result	get_hash(t_allocator allocator, t_writer *writer,\
				t_buffer src) __attribute__((__nonnull__(2)));

#endif
