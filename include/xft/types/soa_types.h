/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:14:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 15:56:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOA_TYPES_H
# define SOA_TYPES_H

# include <xft/primitives.h>
# include <xft/alloc.h>

typedef struct s_soa_field_meta
{
	t_u32a			size;
	t_u32a			offset_from_struct_base;
	t_u32a			size_of_prev_fields;
}	t_soa_field_meta;

typedef struct s_soa_context
{
	t_size				total_struct_size;
	t_size				max_alignment;
	t_size				fields_count;
	t_soa_field_meta	entries[];
}	t_soa_context;

typedef struct s_soa
{
	t_any __restrict__	ptr;
	t_size				occupied_elements;
	t_size				capacity_elements;
	t_size				allocator_bytes_given;
}	t_soa;

#endif
