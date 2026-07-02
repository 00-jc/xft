/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aosoa.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 00:00:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 00:22:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AOSOA_H
# define AOSOA_H

# include "primitives.h"

// ctx is user-passed and it's what drives the aosoa later, no
// deletions.
//
//	[member_size1,member_size1,membersize2,membersize2,membersize1...]
//
// alignment is just the max of all of the elements and every array
// in ctx should be stack-allocated since it's known at compile time.
//
// whole object is only 32 bytes in the stack, buffer and used_per_bucket
// is dynamic
typedef struct s_aosoa_ctx
{
	t_u32							bucket_capacity;
	t_u16							n_members;
	t_u16							max_alignment;
	const t_u32 *__restrict__ const	member_sizes;
	const t_u32 *__restrict__ const	offsets;
}	t_aosoa_ctx;

typedef struct s_aosoa
{
	t_size									n_buckets;
	t_u8 *__restrict__						buffer;
	t_size *__restrict__					used_per_bucket;
	const t_aosoa_ctx *__restrict__			ctx;
}	t_aosoa;

#endif
